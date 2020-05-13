#pragma once
#include "CountingLock.hpp"
#include "DoubleMachineFigure.hpp"

class DoubleMachine
{
public:
    DoubleMachine();

    CountingLock lock;
};