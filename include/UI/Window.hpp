#pragma once
#include "IWindow.hpp"
#include <ncurses.h>
#include <string>

class Window : public IWindow
{
public:
    Window(int width, int height, int x, int y);
    virtual ~Window();

    int x() const override;
    int y() const override;
    void redraw() override;
    void update() override;
    void printAt(int x, int y, const std::string& text);

    WINDOW* raw() const;

private:
    WINDOW* _window;
    int _width;
    int _height;
    int _x;
    int _y;

    void draw();
    void erase();
};