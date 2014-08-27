#include <interceptor.hh>

#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>

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

#include <unistd.h>
#include <sys/types.h>

int main (int argc, char **argv)
{
    const char *iface = argc < 2 ? "any" : argv[1];
    Sniffer s(iface);

    if (geteuid() != 0) {
        // TODO: check user capabilities instead!
        std::cerr << "Expected to fail. Run as root in order to sniff" << std::endl;
        return 77;  // auto-tools recognized: xfail
    }

    try {
        std::cout << "trying with " << iface << std::endl;
        s.open_live();
        std::this_thread::sleep_for(
            std::chrono::seconds(5)
        );
    } catch (const Error &e) {
        std::cout << "phailed " << iface << ": " << e.what() << std::endl;
    }

    return 0;
}
