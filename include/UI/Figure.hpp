#pragma once
#include <ncurses.h>

class Figure
{
public:
    Figure(int width, int height, int rowIndex, int colIndex, bool border = false);
    Figure(const Figure&) = delete;
    Figure(Figure&&) = delete;
    virtual ~Figure();

    Figure& operator=(const Figure&) = delete;
    Figure& operator=(Figure&&) = delete;

private:
    WINDOW* window;
};