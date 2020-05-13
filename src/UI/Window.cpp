#include "Window.hpp"

Window::Window(int width, int height, int x, int y) : _width(width), _height(height), _x(x), _y(y)
{
    draw();
}

Window::~Window()
{
    erase();
}

void Window::redraw()
{
    erase();
    draw();
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
    box(_window, 0, 0);
    refresh();
    wrefresh(_window);
}

void Window::erase()
{
    werase(_window);
    wborder(_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(_window);
    delwin(_window);
}