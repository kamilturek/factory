#include "CountingLock.hpp"

CountingLock::CountingLock(int max) : count(max), maxCount(max)
{
}

void CountingLock::lock()
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

void CountingLock::unlock()
{
    std::unique_lock<std::mutex> lock(mutex);

    if (count == maxCount)
        throw std::logic_error("Occured not allowed release.");

    count++;
    lock.unlock();
    cv.notify_all();
}