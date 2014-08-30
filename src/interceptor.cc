#include <interceptor.hh>
#include <iostream>
#include <pcap.h>
#include <algorithm>

const unsigned SNAP_LEN = 512;
const unsigned READ_TIMEOUT_MS = 1000;

namespace
{

    const char *lookupdev_wrap(char *errbuf)
    {
        const char *dev = pcap_lookupdev(errbuf);
        if (dev == NULL) {
            throw interc::Error(errbuf);
        }
        return dev;
    }

    void pcap_cback (u_char *user, const struct pcap_pkthdr *hdr,
                     const u_char *bytes)
    {
        auto snf = reinterpret_cast<interc::Sniffer *>(user);
        snf->got_packet(*hdr, net::Packet(snf->get_linktype(), bytes, hdr->len));
    }

}

namespace interc
{

    Sniffer::Sniffer ()
        : errbuf(new char[PCAP_ERRBUF_SIZE]),
          handle(NULL),
          linktype(0),
          outqueue(nullptr)
    {
    }

    Event::Event(Type t, const std::string &h)
        : type(t), host(h)
    {
    }

    Sniffer::~Sniffer ()
    {
        if (run_thread.joinable()) {
            close();
        }
        if (handle != NULL) {
            pcap_close(handle);
        }
        delete[] errbuf;
    }

    void Sniffer::open_live (const std::string &iface)
    {
        open_live(iface.c_str());
    }

    void Sniffer::open_offline(const std::string &fn)
    {
        open(pcap_open_offline(fn.c_str(), errbuf));
    }

    void Sniffer::open_live (const char *iface)
    {
        open(pcap_open_live(iface, SNAP_LEN, 0, READ_TIMEOUT_MS, errbuf));
    }

    void Sniffer::open (pcap_t *handle)
    {
        if (handle == NULL) {
            throw interc::Error(errbuf);
        }
        switch (pcap_activate(handle)) {
        case 0:
        case PCAP_WARNING:          // just a regular warning (log it?)
        case PCAP_ERROR_ACTIVATED:  // already activated
            break;

        default:
            throw interc::Error(pcap_geterr(handle));
        }

        linktype = pcap_datalink(handle);
        net::check_datalink_type(linktype);
        run_thread = std::thread(pcap_loop, handle, -1, pcap_cback, (u_char *)this);
    }

    int Sniffer::get_linktype () const
    {
        return linktype;
    }

    void Sniffer::got_packet (const struct pcap_pkthdr &hdr, const net::Packet &pkt)
    {
        if (outqueue != nullptr) {
            Event e(Event::Type::TCP_CONNECT, "127.0.0.1");
            outqueue->push(e);
        }
    }

    void Sniffer::close ()
    {
        if (handle == NULL) {
            throw interc::Error("Not opened");
        }

        pcap_breakloop(handle);
        run_thread.join();
    }

    void Sniffer::set_output(utils::SafeQueue<Event> *outqueue)
    {
        this->outqueue = outqueue;
    }

}
