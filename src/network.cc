#include <network.hh>

namespace net {

    Packet::Packet(const uint8_t *b, size_t s)
      : bytes(b),
        size(s)
    {
    }

    template<> const net::eth::header & Packet::get() const
    {
        const unsigned start = 0;
        const unsigned end = start + sizeof(net::eth::header);
        if (end > size) {
            throw net::Error("Packet size beyond boundaries"); 
        }
        return *((const net::eth::header * const) bytes + start);
    }

}

