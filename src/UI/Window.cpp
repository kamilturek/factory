#include "Window.hpp"
#include <iostream>

Window::Window(int width, int height, int color) : _width(width), _height(height), _x(_invisibleX), _y(_invisibleY), _color(color), _endwin(false)
{
}

Window::Window(int width, int height, int x, int y) : _width(width), _height(height), _x(x), _y(y), _color(0), _endwin(true)
{
    draw();
    update();
}

Window::~Window()
{
    erase();

    if (_endwin)
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

int Window::color() const
{
    return COLOR_PAIR(_color);
}

int Window::width() const
{
    return _width;
}

int Window::height() const
{
    return _height;
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

    wattron(_window, color());
    box(_window, 0, 0);
    wattroff(_window, color());
}

void Window::erase()
{
    wborder(_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(_window);
    delwin(_window);
    _window = nullptr;
}