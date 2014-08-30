#ifndef FILTER_HH
#define FILTER_HH

#include <safequeue.hh>
#include <interceptor.hh>

#include <thread>

namespace filter
{
    class Filter
    {
        public:
            Filter();
            bool check (const interc::Event &event);
    };
}

#endif
