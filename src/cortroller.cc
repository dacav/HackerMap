#include <cortroller.hh>

#include <cassert>

namespace core {

    Core::Core(filter::Filter &flt)
      : filter(flt),
        lookup_out(nullptr),
        view_out(nullptr)
    {
    }

    void Core::run ()
    {
        assert(lookup_out != nullptr);
        assert(view_out != nullptr);

        interc_reader = std::thread([this](){
            bool active = true;
            while (active) {
                try {
                    auto event = interc_in.pop();
                    if (filter.check(event)) {
                        lookup_out->push(event.host);
                    }
                } catch (utils::Terminated &) {
                    active = false;
                }
            }
        });

        lookup_reader = std::thread([this](){
            bool active = true;
            while (active) {
                try {
                    auto mapping = lookup_in.pop();
                    view_out->push(view::DataPoint(mapping.coords));
                } catch (utils::Terminated &) {
                    active = false;
                }
            }
        });

    }

    void Core::set_lookup_output(utils::SafeQueue<std::string> *lo)
    {
        lookup_out = lo;
    }

    void Core::set_view_output(utils::SafeQueue<view::DataPoint> *vo)
    {
        view_out = vo;
    }

    void Core::terminate()
    {
        lookup_in.terminate();
        interc_in.terminate();
    }

    void Core::join()
    {
        interc_reader.join();
        lookup_reader.join();
    }
}
