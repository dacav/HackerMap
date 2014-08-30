#include <safequeue.hh>
#include <iostream>
#include <thread>
#include <cassert>
using namespace utils;

//Waiting time between two bursts of pushes
#define PRODUCER_STEP 100
//Number of bursts
#define PRODUCER_ITERATIONS 15
//Number of pushes per burst
#define PRODUCER_RATE 10000

/*
Right now this test does not take any parameter
Is it possible to run this test automatically with different parameters?
 */
int main(int argc, char** argv){
    SafeQueue<int> q;
    bool good = false;

    std::thread producer([&q](){
        int counter = 0;
        for(int it = 0; it<PRODUCER_ITERATIONS ; it++){
            std::this_thread::sleep_for(std::chrono::milliseconds(PRODUCER_STEP));
            for(int i=0;i<PRODUCER_RATE;i++,counter++) {
                q.push(counter);
            }
        }
    });

    std::thread consumer([&q, &good](){
        int cur = -1;
        while (not good) {
            try {
                int el=q.pop();
                //check if we are popping in the right order
                assert(el==cur+1);
                cur=el;
                std::cout<<el<<std::endl;
            } catch (Terminated &t) {
                good = true;
            }
        }
    });

    producer.join();
    q.terminate();
    consumer.join();
    assert(good);
    return 0;
}
