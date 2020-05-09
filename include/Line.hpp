#pragma once
#include "DoubleMachine.hpp"
#include "HalfMachine.hpp"
#include "SingleMachine.hpp"
#include <memory>

struct Line
{
    std::shared_ptr<DoubleMachine> first;
    std::shared_ptr<SingleMachine> second;
    std::shared_ptr<HalfMachine> thirdOne;
    std::shared_ptr<HalfMachine> thirdTwo;
};