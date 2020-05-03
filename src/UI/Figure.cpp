#include "Figure.hpp"

Figure::Figure(int width, int height, int rowIndex, int colIndex, bool border)
{
    window = newwin(height, width, rowIndex, colIndex);
    if (border)
        box(window, 0, 0);
    refresh();
    wrefresh(window);
}

Figure::~Figure()
{
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    delwin(window);
    endwin();
}