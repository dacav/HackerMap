#ifndef SAFEQUEUE_HH
#define SAFEQUEUE_HH
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <exception>
#include <condition_variable>

namespace utils
{

    class Terminated: public std::exception
    {
      public:
        Terminated() : std::exception() {}
    };

    // The implementation of this class must be in the header because templates
    template <typename T>
    class SafeQueue
    {
      public:
        // Pushes an item into the queue and notify one of the waiting threads
        void push(const T& item)
        {
            std::unique_lock<std::mutex> lock(mutex);
            queue.push(item);
            lock.unlock();
            waiting.notify_one();
        }

        void terminate()
        {
            running = false;
            waiting.notify_all();
        }

        //Waits until there is something in the queue and pops it
        //The lock is managed by the the condition variable
        T pop()
        {
            std::unique_lock<std::mutex> lock(mutex);
            while(queue.empty() && running) {
                waiting.wait(lock);
            }

            if (not running) {
                throw Terminated();
            }
            T t = queue.front();
            queue.pop();
            return t;
        }

        SafeQueue()
            : running(true)
        {
        }

      private:
        std::queue<T> queue;
        std::mutex mutex;
        std::condition_variable waiting;

        std::atomic<bool> running;
    };

}

#endif
