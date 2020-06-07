#pragma once
#include "Window.hpp"

class CarFigure : public Window
{
public:
    CarFigure(int color);

private:
    static constexpr int _carWidth = 15;
    static constexpr int _carHeight = 4;
};