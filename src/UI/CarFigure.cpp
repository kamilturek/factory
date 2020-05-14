#include "CarFigure.hpp"

CarFigure::CarFigure(int color) :
    Window(_carWidth, _carHeight, color)
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