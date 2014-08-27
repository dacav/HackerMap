#include <interceptor.hh>

#include <pcap.h>
#include <algorithm>
#include <sstream>

const unsigned SNAP_LEN = 512;
const unsigned READ_TIMEOUT_MS = 1000;

namespace {

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

namespace interc {

    Sniffer::Sniffer ()
      : errbuf(new char[PCAP_ERRBUF_SIZE]),
        handle(NULL),
        linktype(0),
        iface(lookupdev_wrap(errbuf))
    {
    }

    Sniffer::Sniffer (const std::string &_iface)
      : Sniffer(_iface.c_str())
    {
    }

    Sniffer::Sniffer (const char *_iface)
      : errbuf(new char[PCAP_ERRBUF_SIZE]),
        handle(NULL),
        linktype(0),
        iface(_iface)
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

    void Sniffer::open_live ()
    {
        handle = pcap_open_live(iface.c_str(), SNAP_LEN, 0, READ_TIMEOUT_MS, errbuf);
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
        switch (linktype = pcap_datalink(handle)) {
            case DLT_EN10MB:        // - Ethernet
            case DLT_IEEE802_11:    // - WiFi
            case DLT_LINUX_SLL:     // - fake header for "any" interface
                break;              // ...are supported. Go on.

            default:
                std::stringstream err;
                err << "Unsupported network type: " << linktype
                    << ". See http://www.tcpdump.org/linktypes.html";
                throw interc::Error(err.str());
        }
        run_thread = std::thread(pcap_loop, handle, -1, pcap_cback, (u_char *)this);
    }

    int Sniffer::get_linktype () const
    {
        return linktype;
    }

    void Sniffer::got_packet (const struct pcap_pkthdr &hdr, const net::Packet &pkt)
    {
    }

    void Sniffer::close ()
    {
        if (handle == NULL) {
            throw interc::Error("Not opened");
        }

        pcap_breakloop(handle);
        run_thread.join();
    }

}
