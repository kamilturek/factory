#pragma once
#include <atomic>

class FactoryState
{
public:
    FactoryState(bool isWorking);

    std::atomic<bool> isWorking;
};