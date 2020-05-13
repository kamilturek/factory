#pragma once
#include "Window.hpp"

class CarFigure : public Window
{
public:
    CarFigure();

    void moveTo(int x, int y);
    void hide();

private:
    static constexpr int _width = 15;
    static constexpr int _height = 4;
};