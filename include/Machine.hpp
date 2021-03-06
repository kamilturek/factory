#pragma once
#include <atomic>
#include <condition_variable>
#include <mutex>

class Machine
{
public:
    std::mutex mutex;
    std::mutex conservationMutex;
    std::condition_variable cv;
    std::atomic<int> condition = 100;

    std::atomic<int> x;
    std::atomic<int> y;
};