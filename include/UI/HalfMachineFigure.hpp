#pragma once
#include "Window.hpp"
#include "WindowSet.hpp"

class HalfMachineFigure : public WindowSet
{
public:
    HalfMachineFigure(int x, int y, bool drawStand, int number);

    void redraw() override;

private:
    const int _number;
};