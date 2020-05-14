#pragma once
#include "Window.hpp"
#include "WindowSet.hpp"
#include <memory>

class SingleMachineFigure : public WindowSet
{
public:
    SingleMachineFigure(int x, int y, const int number);

    void redraw() override;

private:
    const int _number;
};