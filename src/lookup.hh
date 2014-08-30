#ifndef LOOKUP_HH
#define LOOKUP_HH

#include <string>
#include <safequeue.hh>
#include <thread>

namespace lookup {

    struct Coords {
        const double longitude;
        const double latitude;

        Coords(double longitude, double latitude);
    };

    class GeoIp {
        public:
            GeoIp(const std::string &server);
            //Coords lookup(net::ipv4...);
            void run();
            void terminate();
            void set_output(utils::SafeQueue<Coords>* output_queue);
            const std::string server;
            utils::SafeQueue<std::string> messages;
            void join();
        private:
            Coords lookup(const std::string &address);
            utils::SafeQueue<Coords>* output;
            std::thread my_thread;
    };

}

#endif // LOOKUP_HH
