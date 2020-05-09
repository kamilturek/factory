#pragma once
#include "CountingLock.hpp"

class DoubleMachine
{
public:
    DoubleMachine();

    CountingLock lock;
};