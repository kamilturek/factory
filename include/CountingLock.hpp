#pragma once
#include <condition_variable>
#include <mutex>

class CountingLock
{
public:
    explicit CountingLock(int max);

    void acquire();
    void release();

private:
    int count;
    const int maxCount;
    std::mutex mutex;
    std::condition_variable cv;
};