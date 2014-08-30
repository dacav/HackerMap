#include <config.h>
#include <iostream>
#include <filter.hh>
#include <cortroller.hh>
#include <lookup.hh>
#include <visualizer.hh>
#include <thread>
using namespace std;

int main (int argc, char **argv)
{
  filter::Filter filter;
  lookup::GeoIp look("www.dacavfuffa.org");
  core::Core core(filter);
  interc::Sniffer interceptor("lo");
  view::Visualizer visual;
  interceptor.set_output(&core.interc_in);
  core.set_lookup_output(&look.messages);
  look.set_output(&core.lookup_in);
  core.set_view_output(&visual.messages);
  look.run();
  visual.run();
  core.run();
  interceptor.open_live();
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    std::cout << "Hello, world! This is " PACKAGE_NAME " version "
        PACKAGE_VERSION << std::endl;
  visual.terminate();
  core.terminate();
  look.terminate();
  visual.join();
  cout<<"Joined visual"<<endl;
  core.join();
  cout<<"Joined core"<<endl;
  look.join();
  cout<<"Joined lookup"<<endl;
  return 0;
}
