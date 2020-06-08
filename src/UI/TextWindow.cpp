#include "TextWindow.hpp"

TextWindow::TextWindow(int width, int height, int x, int y, const std::string& text, bool reversed) :
    Window(width, height, x, y), _text(text), _reversed(reversed)
{
}

void TextWindow::redraw()
{
    const int textX = width() / 2 + static_cast<int>(_text.length()) / 2 - 4;
    const int textY = height() / 2;
    Window::redraw();
    if (_reversed)
        wattron(_window, A_REVERSE);
    printAt(textX, textY, "  " + _text + "  ");
    wattroff(_window, A_REVERSE);
}

void TextWindow::moveTo(int x, int y)
{
    const int textX = width() / 2 + static_cast<int>(_text.length()) / 2 - 4;
    const int textY = height() / 2;
    printAt(textX, textY, "       ");
    Window::moveTo(x, y);
    redraw();
}

void TextWindow::reset()
{
    const int textX = width() / 2 + static_cast<int>(_text.length()) / 2 - 4;
    const int textY = height() / 2;
    printAt(textX, textY, "       ");
    Window::reset();
}