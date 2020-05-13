#include "Config.hpp"
#include "SingleMachineFigure.hpp"

SingleMachineFigure::SingleMachineFigure(int rowIndex, int colIndex) : _currRowIndex(rowIndex), _currColIndex(colIndex)
{
    initializeStand(rowIndex, colIndex);
    initializeMachine(rowIndex, colIndex);
}

void SingleMachineFigure::initializeMachine(int rowIndex, int colIndex)
{
    machine = std::make_unique<Figure>(Config::machineWidth, Config::machineHeight, rowIndex, colIndex, true);
}

void SingleMachineFigure::initializeStand(int rowIndex, int colIndex)
{
    constexpr int offset = 1; 
    stand = std::make_unique<Figure>(Config::standWidth, Config::standHeight, rowIndex + Config::machineHeight - 1, colIndex + offset, true);
}

int SingleMachineFigure::getRowIndex() const
{
    return _currRowIndex;
}

int SingleMachineFigure::getColIndex() const
{
    return _currColIndex;
}