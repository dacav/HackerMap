#include <lookup.hh>
#include <cassert>

namespace lookup
{

    Mapping::Mapping(const std::string& _address, Coords _coords)
        : address(_address), coords(_coords)
    {
    }

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

    void GeoIp::run()
    {
        assert(output);
        my_thread = std::thread([this]() {
            bool active = true;
            while(active) {
                try {
                    std::string address = messages.pop();
                    output->push(Mapping(address,lookup(address)));
                } catch(utils::Terminated &t) {
                    active=false;
                }
            }
        });
    }
    void GeoIp::terminate()
    {
        messages.terminate();
    }

    void GeoIp::set_output(utils::SafeQueue<Mapping>* output_queue)
    {
        output=output_queue;
    }
    void GeoIp::join()
    {
        my_thread.join();
    }
}
