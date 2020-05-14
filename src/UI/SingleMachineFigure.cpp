#include "SingleMachineFigure.hpp"

SingleMachineFigure::SingleMachineFigure(int x, int y, const int number) : _number(number)
{
    constexpr int machineWidth = 21;
    constexpr int machineHeight = 3;
    constexpr int standWidth = 19;
    constexpr int standHeight = 5;
    constexpr int offset = 1;

    _windows.push_back(std::make_unique<Window>(standWidth, standHeight, x + offset, y + machineHeight - offset));
    _windows.push_back(std::make_unique<Window>(machineWidth, machineHeight, x, y));
}

void SingleMachineFigure::redraw()
{
    WindowSet::redraw();
    mvprintw(_windows.back()->y() + 1, _windows.front()->x() + 9, std::to_string(_number).c_str());
}