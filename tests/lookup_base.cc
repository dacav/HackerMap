#include <lookup.hh>

#include <iostream>

int main (int argc, char **argv)
{
    auto coords = lookup::GeoIp("geoip.example.com").lookup("oglaf.com");
    std::cout << coords.longitude << ", " << coords.latitude << std::endl;

    return 0;
}
