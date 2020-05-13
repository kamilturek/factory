#include "HalfMachineFigure.hpp"

HalfMachineFigure::HalfMachineFigure(int x, int y, bool drawStand) : WindowSet()
{
    constexpr int machineWidth = 21;
    constexpr int machineHeight = 3;
    constexpr int standWidth = 19;
    constexpr int standHeight = 5;
    constexpr int offset = 1;
    
    if (drawStand)
        _windows.push_back(std::make_unique<Window>(standWidth, standHeight, x + offset, y + machineHeight - offset));
    _windows.push_back(std::make_unique<Window>(machineWidth, machineHeight, x, y));
}