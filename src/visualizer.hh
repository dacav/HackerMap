#ifndef VISUALIZER_HH
#define VISUALIZER_HH
#include <lookup.hh>

namespace view {
    class DataPoint{
    public:
      const lookup::Coords coords;
      DataPoint(const lookup::Coords& coo);
    };

    class Visualizer {
        public:
            void run();
            void terminate();
            void join();
            utils::SafeQueue<DataPoint> messages;
            std::thread my_thread;
    };
}

#endif // VISUALIZER_HH
