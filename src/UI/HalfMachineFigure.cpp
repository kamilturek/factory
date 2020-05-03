#include "HalfMachineFigure.hpp"
#include "Config.hpp"

HalfMachineFigure::HalfMachineFigure(int rowIndex, int colIndex, bool hasStand)
{
    if (hasStand)
        initializeStand(rowIndex, colIndex);
    initializeMachine(rowIndex, colIndex);
}

void HalfMachineFigure::initializeMachine(int rowIndex, int colIndex)
{
    machine = std::make_unique<Figure>(Config::machineWidth, Config::machineHeight, rowIndex, colIndex, true);
}

void HalfMachineFigure::initializeStand(int rowIndex, int colIndex)
{
    constexpr int offset = 1;
    stand = std::make_unique<Figure>(Config::standWidth, Config::standHeight, rowIndex + Config::machineHeight - 1, colIndex + offset, true);
}