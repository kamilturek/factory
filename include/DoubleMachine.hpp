#pragma once
#include "CountingLock.hpp"

class DoubleMachine
{
public:
    DoubleMachine();

private:
    CountingLock lock;
};