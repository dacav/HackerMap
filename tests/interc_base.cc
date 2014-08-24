#include "../src/interceptor.hh"
#include <cassert>
#include <iostream>

using namespace interc;

namespace {

    bool check_open (Sniffer &sn)
    {
        try {
            sn.open_live();
        } catch (const Error &e) {
            std::cerr << "cannot open: " << e.what() << std::endl;
            return false;
        }

        return true;
    }

}

int main (int argc, char **argv)
{
    bool good = false;

    try {
        /* "baracca" is hardly a network interface */
        Sniffer("baracca").open_live();
    } catch (const Error &e) {
        good = true;
    }
    assert(good);

    Sniffer s0;
    good = check_open(s0);
    Sniffer s1(s0.iface);
    good = check_open(s1);

    return 0;
}
