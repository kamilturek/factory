#pragma once
#include "CountingMutex.hpp"
#include "DoubleMachineFigure.hpp"

class DoubleMachine
{
public:
    DoubleMachine();

    CountingMutex lock;
};