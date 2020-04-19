#pragma once
#include <condition_variable>
#include <mutex>

class Machine
{
public:
    std::mutex mutex;
    std::condition_variable cv;
};