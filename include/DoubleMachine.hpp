#pragma once
#include <atomic>
#include "CountingMutex.hpp"
#include "DoubleMachineFigure.hpp"
#include "Machine.hpp"

class DoubleMachine : public Machine
{
public:
    DoubleMachine();

    CountingMutex lock;
};