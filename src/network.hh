#ifndef NETWORK_HH
#define NETWORK_HH

#include <cstdint>
#include <netinet/in.h>
#include <stdexcept>
#include <pcap.h>

namespace net
{

    void check_datalink_type(int linktype);

    namespace eth
    {
        const unsigned ADDR_LEN = 6;

        struct header {
            uint8_t dhost[ADDR_LEN];
            uint8_t shost[ADDR_LEN];
            uint16_t type;
        };
    }

    namespace any
    {
        const unsigned ADDR_LEN = 8;

        // http://www.tcpdump.org/linktypes/LINKTYPE_LINUX_SLL.html
        struct header {
            uint16_t type;
            uint16_t arp;
            uint16_t addrlen;
            uint8_t addr[ADDR_LEN];
            uint16_t protocol;
        };
    }

    namespace ipv4
    {
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

    class Error: public std::runtime_error
    {
        public:
            Error(const char *msg) : std::runtime_error(msg) {}
            Error(const std::string & msg) : std::runtime_error(msg) {}
    };

    class Packet
    {
        public:
            Packet(int linktype, const uint8_t *bytes, size_t size);

            const int linktype;
            const uint8_t * const bytes;
            const size_t size;

            template<typename T> const T & get() const;

        private:
            void datalink_require(int linktype) const;
            template<typename T> const T & chunk_require(off_t start) const;
    };

}

#endif // NETWORK_HH
