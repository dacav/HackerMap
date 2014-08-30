#ifndef LOOKUP_HH
#define LOOKUP_HH

#include <string>

namespace lookup {

    struct Coords {
        const double longitude;
        const double latitude;

        Coords(double longitude, double latitude);
    };

    class GeoIp {
        public:
            GeoIp(const std::string &server);

            Coords lookup(const std::string &address);
            //Coords lookup(net::ipv4...);

            const std::string server;
    };

}

#endif // LOOKUP_HH
