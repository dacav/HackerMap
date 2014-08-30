#ifndef INTERCEPTOR_HH
#define INTERCEPTOR_HH

#include <network.hh>
#include <safequeue.hh>

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

    struct Event {
        enum Type {
            TCP_CONNECT = 0
        } type;
        const std::string host;

        Event(Type type, const std::string &host);
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
            int get_linktype() const;
      
           void set_output(utils::SafeQueue<Event> *outqueue);
        private:
            char *errbuf;
            pcap_t *handle;
            std::thread run_thread;
            int linktype;
            utils::SafeQueue<Event> *outqueue;

        public:
            const std::string iface;
    };

}

#endif // INTERCEPTOR_HH
