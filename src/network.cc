#include <network.hh>

namespace net {

    Packet::Packet(int lt, const uint8_t *b, size_t s)
      : linktype(lt),
        bytes(b),
        size(s)
    {
    }

    void Packet::datalink_require(int req_lt) const
    {
        if (req_lt != linktype) {
            throw net::Error("Invalid datalink header requested"); 
        }
    }

    template<typename T> const T & Packet::chunk_require(off_t start) const
    {
        if (start + sizeof(T) >= size) {
            throw net::Error("Packet size beyond boundaries"); 
        }
        return *reinterpret_cast<const T *>(bytes + start);
    }

    template<> const net::eth::header & Packet::get() const
    {
        datalink_require(DLT_EN10MB);
        return chunk_require<net::eth::header>(0);
    }

    template<> const net::any::header & Packet::get() const
    {
        datalink_require(DLT_LINUX_SLL);
        return chunk_require<net::any::header>(0);
    }

}

