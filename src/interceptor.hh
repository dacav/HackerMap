#ifndef INTERCEPTOR_HH
#define INTERCEPTOR_HH

#include <network.hh>

#include <string>
#include <stdexcept>
#include <thread>

#include <pcap.h>

namespace interc {

    class Error: public std::runtime_error {
        public:
            Error(const char *msg) : std::runtime_error(msg) {}
            Error(const std::string & msg) : std::runtime_error(msg) {}
    };

    class Sniffer {
        public:
            explicit Sniffer(const char *iface);
            explicit Sniffer(const std::string &iface);
            Sniffer();
            ~Sniffer();

            void open_live();
            void close();

            void got_packet(const struct pcap_pkthdr &hdr, const net::Packet &pkt);

        private:
            char *errbuf;
            pcap_t *handle;
            std::thread run_thread;

        public:
            const std::string iface;
    };

}

#endif // INTERCEPTOR_HH
