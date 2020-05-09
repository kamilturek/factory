#include "Figure.hpp"
#include <thread>

Figure::Figure(int width, int height, int rowIndex, int colIndex, bool border) : _width(width), _height(height), _currRowIndex(rowIndex), _currColIndex(colIndex), _border(border)
{
    draw();
}

Figure::~Figure()
{
    erase();
    endwin();
}

void Figure::draw()
{
    window = newwin(_height, _width, _currRowIndex, _currColIndex);
    if (_border)
        box(window, 0, 0);
    refresh();
    wrefresh(window);
}

void Figure::erase()
{
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    delwin(window);
}

void Figure::redraw()
{
    erase();
    draw();
}

void Figure::moveTo(int rowIndex, int colIndex)
{
    _currRowIndex = rowIndex;
    _currColIndex = colIndex;
    redraw();
}