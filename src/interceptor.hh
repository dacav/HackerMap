#ifndef INTERCEPTOR_HH
#define INTERCEPTOR_HH

#include <string>
#include <stdexcept>

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

        private:
            char *errbuf;
            pcap_t *handle;

        public:
            const std::string iface;
    };

}

#endif // INTERCEPTOR_HH
