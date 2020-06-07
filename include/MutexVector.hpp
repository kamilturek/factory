#pragma once
#include <mutex>
#include <vector>

template<class T>
class MutexVector : public std::vector<T>
{
public:
    std::mutex mutex;
};