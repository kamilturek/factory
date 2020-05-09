#pragma once
#include <ncurses.h>

class Figure
{
public:
    Figure(int width, int height, int rowIndex, int colIndex, bool border = false);
    Figure(const Figure&) = delete;
    Figure(Figure&&) = delete;
    virtual ~Figure();

    void moveTo(int rowIndex, int colIndex);

    Figure& operator=(const Figure&) = delete;
    Figure& operator=(Figure&&) = delete;

private:
    WINDOW* window;
    int _width;
    int _height;
    int _currRowIndex;
    int _currColIndex;
    bool _border;

    void draw();
    void erase();
    void redraw();
};