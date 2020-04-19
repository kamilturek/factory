#pragma once
#include "DoubleMachine.hpp"
#include "HalfMachine.hpp"
#include "SingleMachine.hpp"
#include <memory>

struct Line
{
    std::unique_ptr<DoubleMachine> first;
    std::unique_ptr<SingleMachine> second;
    std::shared_ptr<HalfMachine> thirdOne;
    std::shared_ptr<HalfMachine> thirdTwo;
};