#include <visualizer.hh>
#include <iostream>
using namespace std;

namespace view {
       DataPoint::DataPoint(const lookup::Coords& coo) :
        coords(coo)
      {
      }

    void Visualizer::run(){
      my_thread = std::thread([this](){
          bool active = true;
          while(active){
            try{
              DataPoint out = messages.pop();
              cout<<out.coords.latitude<<" "<<out.coords.longitude<<endl;
            }catch(utils::Terminated &t){
              active=false;
            }
          }
        });
    }
    void Visualizer::terminate(){
        messages.terminate();
    }

    void Visualizer::join(){
        my_thread.join();
    }
}
