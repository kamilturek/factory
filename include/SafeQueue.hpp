#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>

template <class T>
class SafeQueue
{
public:
    void push(const T& value)
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _queue.push(value);
        lock.unlock();
        _cv.notify_one();       
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _cv.wait(lock, [&]
        {
            return !_queue.empty();
        });
    }

private:
    std::condition_variable _cv;
    std::mutex _mutex;
    std::queue<T> _queue;
};