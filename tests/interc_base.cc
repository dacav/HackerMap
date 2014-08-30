#include <interceptor.hh>

#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#include <unistd.h>
#include <sys/types.h>

using namespace interc;

int main (int argc, char **argv)
{
    const char *iface = argc < 2 ? "any" : argv[1];
    Sniffer s;

    if (geteuid() != 0) {
        // TODO: check user capabilities instead!
        std::cerr << "Expected to fail. Run as root in order to sniff" << std::endl;
        return 77;  // auto-tools recognized: xfail
    }

    try {
        std::cout << "trying with " << iface << std::endl;
        s.open_live(iface);
        std::this_thread::sleep_for(
            std::chrono::seconds(5)
        );
    } catch (const Error &e) {
        std::cout << "phailed " << iface << ": " << e.what() << std::endl;
    }

    return 0;
}
