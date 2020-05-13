#include "CarFigure.hpp"

CarFigure::CarFigure() :
    Window(_width, _height)
{
}

void CarFigure::moveTo(int x, int y)
{
    _x = x;
    _y = y;
    redraw();
}

void CarFigure::hide()
{
    moveTo(_invisibleX, _invisibleY);
}