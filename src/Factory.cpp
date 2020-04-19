#include "Factory.hpp"
#include "DoubleMachine.hpp"
#include "HalfMachine.hpp"
#include "SingleMachine.hpp"
#include <iostream>
#include <memory>

Factory::Factory()
{
    setupLines();
}

void Factory::setupLines()
{
    lines.at(0).first = std::make_unique<DoubleMachine>();
    lines.at(0).second = std::make_unique<SingleMachine>();
    lines.at(0).thirdOne = std::make_shared<HalfMachine>();
    lines.at(0).thirdTwo = std::make_shared<HalfMachine>();

    lines.at(1).first = std::make_unique<DoubleMachine>();
    lines.at(1).second = std::make_unique<SingleMachine>();
    lines.at(1).thirdOne = lines.at(0).thirdTwo;
    lines.at(1).thirdTwo = std::make_shared<HalfMachine>();

    lines.at(2).first = std::make_unique<DoubleMachine>();
    lines.at(2).second = std::make_unique<SingleMachine>();
    lines.at(2).thirdOne = lines.at(1).thirdTwo;
    lines.at(2).thirdTwo = std::make_shared<HalfMachine>();

    lines.at(2).first = std::make_unique<DoubleMachine>();
    lines.at(2).second = std::make_unique<SingleMachine>();
    lines.at(2).thirdOne = lines.at(2).thirdTwo;
    lines.at(2).thirdTwo = std::make_shared<HalfMachine>();
}