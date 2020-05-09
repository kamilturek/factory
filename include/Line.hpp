#pragma once
#include "DoubleMachine.hpp"
#include "HalfMachine.hpp"
#include "SingleMachine.hpp"
#include <memory>

struct Line
{
    unsigned int number;
    std::shared_ptr<DoubleMachine> first;
    std::shared_ptr<SingleMachine> second;
    std::shared_ptr<HalfMachine> thirdOne;
    std::shared_ptr<HalfMachine> thirdTwo;
};