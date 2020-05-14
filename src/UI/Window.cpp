#include "Window.hpp"
#include <iostream>

Window::Window(int width, int height, int color) : _width(width), _height(height), _x(_invisibleX), _y(_invisibleY), _color(color)
{
}

Window::Window(int width, int height, int x, int y) : _width(width), _height(height), _x(x), _y(y), _color(0)
{
    draw();
    update();
}

Window::~Window()
{
    erase();
    endwin();
}

void Window::redraw()
{
    erase();
    draw();
    update();
}

void Window::update()
{
    refresh();
    wrefresh(_window);
}

int Window::x() const
{
    return _x;
}

int Window::y() const
{
    return _y;
}

void Window::printAt(int x, int y, const std::string& text)
{
    mvwprintw(_window, y, x, text.c_str());
    update();
}

WINDOW* Window::raw() const
{
    return _window;
}

void Window::draw()
{
    _window = newwin(_height, _width, _y, _x);

    wattron(_window, COLOR_PAIR(_color));
    box(_window, 0, 0);
    wattroff(_window, COLOR_PAIR(_color));
}

void Window::erase()
{
    werase(_window);
    wborder(_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(_window);
    delwin(_window);
}