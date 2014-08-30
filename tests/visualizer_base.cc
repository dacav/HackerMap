#include <visualizer.hh>
#include <lookup.hh>

int main (int argc, char **argv)
{
    view::Visualizer vis;
    vis.run();
    for(int i=0; i<100; i++) {
        vis.messages.push(lookup::Coords(i,i));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    vis.terminate();
    vis.join();
    return 0;
}
