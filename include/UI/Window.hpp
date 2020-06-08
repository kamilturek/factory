#pragma once
#include "IWindow.hpp"
#include <ncurses.h>
#include <string>

class Window : public IWindow
{
public:
    Window(int width, int height, int color);
    Window(int width, int height, int x, int y);
    virtual ~Window();

    int color() const;
    int width() const;
    int height() const;
    int x() const override;
    int y() const override;
    void redraw() override;
    void update() override;
    void hide();
    void reset();
    void moveTo(int x, int y);
    void printAt(int x, int y, const std::string& text);

    WINDOW* raw() const;

protected:
    static constexpr int _invisibleX = -99;
    static constexpr int _invisibleY = -99;

    int _width;
    int _height;
    int _x;
    int _y;
    int _startX;
    int _startY;
    int _color;
    bool _endwin;

    void draw();
    void erase();

    WINDOW* _window = nullptr;
};