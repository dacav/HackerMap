#ifndef SAFEQUEUE_HH
#define SAFEQUEUE_HH
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace utils {
  // The implementation of this class must be in the header because templates
  template <typename T> 
  class safequeue
  {
  public:
    // Pushes an item into the queue and notify one of the waiting threads
    void push(const T& item){
      std::unique_lock<std::mutex> lock(mutex);
      queue.push(item);
      lock.unlock();
      waiting.notify_one();
    }

    //Waits until there is something in the queue and pops it
    //The lock is managed by the the condition variable
    T pop(){
      std::unique_lock<std::mutex> lock(mutex);
      while(queue.empty()){
        waiting.wait(lock);
      }      
      T t = queue.front();
      queue.pop();
      return t;
    }

  private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable waiting;
  };

}

#endif
