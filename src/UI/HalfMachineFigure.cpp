#include "HalfMachineFigure.hpp"

HalfMachineFigure::HalfMachineFigure(int x, int y, bool drawStand, int number) : WindowSet(), _number(number)
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

void HalfMachineFigure::redraw()
{
    WindowSet::redraw();
    if (_windows.size() == 2)
        mvprintw(_windows.front()->y() + 2, _windows.front()->x() + 9, std::to_string(_number).c_str());
}