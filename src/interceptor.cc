#include <interceptor.hh>

#include <pcap.h>
#include <algorithm>

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
        ((interc::Sniffer *)user)->got_packet(*hdr, net::Packet(bytes, hdr->len));
    }

}

namespace interc {

    Sniffer::Sniffer ()
      : errbuf(new char[PCAP_ERRBUF_SIZE]),
        handle(NULL),
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
        handle = pcap_open_live(iface.c_str(), SNAP_LEN, 0,
            READ_TIMEOUT_MS, errbuf
        );
        if (handle == NULL) {
            throw interc::Error(errbuf);
        }

        run_thread = std::thread(pcap_loop, handle, -1, pcap_cback, (u_char *)this);
    }

    void Sniffer::got_packet(const struct pcap_pkthdr &hdr, const net::Packet &pkt)
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
