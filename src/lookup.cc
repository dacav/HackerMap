#include <lookup.hh>

namespace lookup {

    Coords::Coords(double lg, double lt)
      : longitude(lg),
        latitude(lt)
    {
    }

    GeoIp::GeoIp(const std::string &srv)
      : server(srv)
    {
    }

    Coords GeoIp::lookup(const std::string &address)
    {
        return Coords(10, 20);
    }

}
