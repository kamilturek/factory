#include "DoubleMachineFigure.hpp"

DoubleMachineFigure::DoubleMachineFigure(int x, int y) : WindowSet()
{
    constexpr int machineWidth = 21;
    constexpr int machineHeight = 3;
    constexpr int standWidth = 19;
    constexpr int standHeight = 5;
    constexpr int offset = 1;
    
    _windows.push_back(std::make_unique<Window>(standWidth, standHeight, x + offset, y + offset));
    _windows.push_back(std::make_unique<Window>(standWidth, standHeight, x + offset, y + standHeight + machineHeight - offset));
    _windows.push_back(std::make_unique<Window>(machineWidth, machineHeight, x, y + standHeight));
}

bool DoubleMachineFigure::isUpperStandTaken() const
{
    return _upperStandTaken;
}

void DoubleMachineFigure::setUpperStandTaken(bool value)
{
    _upperStandTaken = value;
}