#include "DoubleMachineFigure.hpp"
#include "Config.hpp"

DoubleMachineFigure::DoubleMachineFigure(int rowIndex, int colIndex)
{
    initializeStands(rowIndex, colIndex);
    initializeMachine(rowIndex, colIndex);
}

void DoubleMachineFigure::initializeMachine(int rowIndex, int colIndex)
{
    machine = std::make_unique<Figure>(Config::machineWidth, Config::machineHeight, rowIndex + Config::standHeight, colIndex, true);
}

void DoubleMachineFigure::initializeStands(int rowIndex, int colIndex)
{
    constexpr int offset = 1;
    stands.first = std::make_unique<Figure>(Config::standWidth, Config::standHeight, rowIndex + offset, colIndex + offset, true);
    stands.second = std::make_unique<Figure>(Config::standWidth, Config::standHeight, rowIndex + Config::standHeight + Config::machineHeight - offset, colIndex + offset, true);
}