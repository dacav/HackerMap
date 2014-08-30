#include <network.hh>
#include <interceptor.hh>
#include <safequeue.hh>

#include <cstdint>
#include <cassert>
#include <iostream>

#include <pcap.h>

using namespace std;
using namespace interc;
using namespace utils;

/* This tests the case in which we ask an item from the header */
void good ()
{
    uint8_t buf[200];
    for (int i = 0; i < 3; i ++) {
        buf[i] = i + 1;
    }

    net::Packet p(DLT_LINUX_SLL, buf, sizeof(buf));
    auto hdr = p.get<net::any::header>();
    for (int i = 0; i < 3; i ++) {
        cout << hex << hdr.type << endl;
        assert(hdr.type == 0x0201);
    }
}

/* This tests the case in which we ask an item beyond the size of the
 * buffer.  */
void bad ()
{
    uint8_t buf[5];
    for (int i = 0; i < 5; i ++) {
        buf[i] = i + 1;
    }

    net::Packet p(DLT_LINUX_SLL, buf, sizeof(buf));
    try {
        p.get<net::any::header>();
        assert(false);
    } catch (net::Error &e) {
        cout << "Got expected error: " << e.what() << ". Good" << endl;
    }
}

void ugly()
{
    SafeQueue<Event> queue;
    Sniffer(&queue).open_offline("./dump.pcap");

}

int main (int argc, char **argv)
{
    good() ;
    bad();
}
