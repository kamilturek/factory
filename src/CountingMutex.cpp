#include "CountingMutex.hpp"

CountingMutex::CountingMutex(int max) : count(max), maxCount(max)
{
}

void CountingMutex::lock()
{
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [&]
    {
        if (count > 0)
        {
            count--;
            return true;
        }
        return false;
    });
}

void CountingMutex::unlock()
{
    std::unique_lock<std::mutex> lock(mutex);

    if (count == maxCount)
        throw std::logic_error("Occured not allowed release.");

    count++;
    lock.unlock();
    cv.notify_all();
}