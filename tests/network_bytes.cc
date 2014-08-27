#include "../src/network.hh"
#include <cstdint>
#include <cassert>
#include <iostream>

using namespace net;
using namespace std;

/* This tests the case in which we ask an item from the header */
void good ()
{
    uint8_t buf[200];
    for (int i = 0; i < 3; i ++) {
        buf[i] = i + 1;
    }

    Packet p(buf, sizeof(buf));
    auto hdr = p.get<eth::header>();
    for (int i = 0; i < 3; i ++) {
        cout << hex << (int)hdr->dhost[i] << endl;
        assert(hdr->dhost[i] == i + 1);
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

    Packet p(buf, sizeof(buf));
    try {
        p.get<eth::header>();
        assert(false);
    } catch (Error &e) {
        /* Exception because buffer size is below size of ethernet
         * header. */
        cout << "Got expected error: " << e.what() << ". Good" << endl;
    }
}


int main (int argc, char **argv)
{
    good() ;
    bad();
}
