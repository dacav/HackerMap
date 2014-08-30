#ifndef INTERCEPTOR_HH
#define INTERCEPTOR_HH

#include <network.hh>
#include <safequeue.hh>

#include <string>
#include <stdexcept>
#include <thread>

#include <pcap.h>

namespace interc
{

    class Error: public std::runtime_error
    {
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

    class Sniffer
    {
        public:
            Sniffer(utils::SafeQueue<Event> *outqueue = nullptr);
            ~Sniffer();

            void open_live(const std::string &iface);
            void open_live(const char *iface);
            void open_offline(const std::string &fn);
            void open_offline(const char *fn);
            void close();

            void got_packet(const struct pcap_pkthdr &hdr, const net::Packet &pkt);
            int get_linktype() const;

            void set_output(utils::SafeQueue<Event> * const outqueue);

        private:
            char *errbuf;
            pcap_t *handle;
            std::thread run_thread;
            int linktype;
            utils::SafeQueue<Event> *outqueue;

            void open (pcap_t *handle);
            bool live;
    };

}

#endif // INTERCEPTOR_HH
