#ifndef SAFEQUEUE_HH
#define SAFEQUEUE_HH
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace utils {

  template <typename T> 
  class safequeue
  {
  public:
    void push(const T& item){
      std::unique_lock<std::mutex> lock(mutex);
      queue.push(item);
      lock.unlock();
      waiting.notify_one();
    }

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
