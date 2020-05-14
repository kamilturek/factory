#pragma once
#include <condition_variable>
#include <mutex>

// Inspired by C++20's std::counting_semaphore
// Not available in any compiler on 15.05.2020

// Meets C++ BasicLockable requirements

class CountingLock
{
public:
    explicit CountingLock(int max);

    void lock();
    void unlock();

private:
    int count;
    const int maxCount;
    std::mutex mutex;
    std::condition_variable cv;
};