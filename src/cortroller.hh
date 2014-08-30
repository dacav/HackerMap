#ifndef CORTROLLER_H
#define CORTROLLER_H

#include <safequeue.hh>
#include <interceptor.hh>
#include <filter.hh>
#include <lookup.hh>
#include <visualizer.hh>

#include <thread>
#include <string>

namespace core
{

    class Core
    {
      public:
        Core(filter::Filter &flt);

        utils::SafeQueue<lookup::Mapping> lookup_in;
        utils::SafeQueue<interc::Event> interc_in;

        void run();
        void terminate();
        void join();

        void set_lookup_output(utils::SafeQueue<std::string> *lo);
        void set_view_output(utils::SafeQueue<view::DataPoint> *vo);
      private:
        filter::Filter &filter;

        std::thread interc_reader;
        std::thread lookup_reader;

        utils::SafeQueue<std::string> *lookup_out;
        utils::SafeQueue<view::DataPoint> *view_out;
    };

}

#endif // CORTROLLER_H
