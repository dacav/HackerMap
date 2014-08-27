#ifndef NETWORK_HH
#define NETWORK_HH

#include <cstdint>
#include <netinet/in.h>
#include <stdexcept>

namespace net {

    namespace eth {
        const unsigned ADDR_LEN = 6;

        struct header {
            uint8_t dhost[ADDR_LEN];
            uint8_t shost[ADDR_LEN];
            uint16_t type;
        };
    }

    namespace ipv4 {
        struct header {
            uint8_t version;
            uint8_t tos;
            uint16_t len;
            uint16_t id;
            uint16_t offset;
            uint8_t ttl;
            uint8_t protocol;
            uint16_t checksum;
            struct in_addr src;
            struct in_addr dst;
        };
    }

    class Error: public std::runtime_error {
        public:
            Error(const char *msg) : std::runtime_error(msg) {}
            Error(const std::string & msg) : std::runtime_error(msg) {}
    };

    class Packet {
        public:
            Packet(const uint8_t *bytes, size_t size);

            const uint8_t *bytes;
            const size_t size;

            template<typename T> const T & get() const;
    };

}

#endif // NETWORK_HH
