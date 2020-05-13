#pragma once
#include <ncurses.h>

class Figure
{
public:
    Figure(int width, int height, int rowIndex, int colIndex, bool border = false);
    Figure(const Figure&) = delete;
    Figure(Figure&&) = delete;
    virtual ~Figure();

    void refresh();
    void moveTo(int rowIndex, int colIndex);
    void setBorder(bool value);
    void draw();
    void erase();

    Figure& operator=(const Figure&) = delete;
    Figure& operator=(Figure&&) = delete;

private:
    WINDOW* window;
    int _width;
    int _height;
    int _currRowIndex;
    int _currColIndex;
    bool _border;

};