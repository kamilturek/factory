#pragma once
#include "DoubleMachine.hpp"
#include "HalfMachine.hpp"
#include "Machine.hpp"
#include "SingleMachine.hpp"
#include <memory>
#include <vector>

struct Line
{
    unsigned int number;
    std::shared_ptr<DoubleMachine> first;
    std::shared_ptr<SingleMachine> second;
    std::shared_ptr<HalfMachine> thirdOne;
    std::shared_ptr<HalfMachine> thirdTwo;

    std::array<std::shared_ptr<Machine>, 4> machines() const
    {
        return { first, second, thirdOne, thirdTwo };
    }
};