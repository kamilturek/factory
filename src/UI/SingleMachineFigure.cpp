#include "SingleMachineFigure.hpp"

SingleMachineFigure::SingleMachineFigure(int rowIndex, int colIndex)
{
    initializeStand(rowIndex, colIndex);
    initializeMachine(rowIndex, colIndex);
}

void SingleMachineFigure::initializeMachine(int rowIndex, int colIndex)
{
    machine = std::make_unique<Figure>(machineWidth, machineHeight, rowIndex, colIndex, true);
}

void SingleMachineFigure::initializeStand(int rowIndex, int colIndex)
{
    constexpr int offset = 1; 
    stand = std::make_unique<Figure>(standWidth, standHeight, rowIndex + machineHeight - 1, colIndex + offset, true);
}