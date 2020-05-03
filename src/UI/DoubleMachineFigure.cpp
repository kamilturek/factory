#include "DoubleMachineFigure.hpp"

DoubleMachineFigure::DoubleMachineFigure(int rowIndex, int colIndex)
{
    initializeStands(rowIndex, colIndex);
    initializeMachine(rowIndex, colIndex);
}

void DoubleMachineFigure::initializeMachine(int rowIndex, int colIndex)
{
    machine = std::make_unique<Figure>(machineWidth, machineHeight, rowIndex + standHeight, colIndex, true);
}

void DoubleMachineFigure::initializeStands(int rowIndex, int colIndex)
{
    constexpr int offset = 1;
    stands.first = std::make_unique<Figure>(standWidth, standHeight, rowIndex + offset, colIndex + offset, true);
    stands.second = std::make_unique<Figure>(standWidth, standHeight, rowIndex + (standHeight + machineHeight - offset), colIndex + offset, true);
}