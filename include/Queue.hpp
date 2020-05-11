#pragma once
#include <mutex>
#include <queue>

template<class T>
struct Queue
{
    std::queue<T> queue;
    std::mutex mutex;
};