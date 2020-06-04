#include "TextWindow.hpp"

TextWindow::TextWindow(int width, int height, int x, int y, const std::string& text) : Window(width, height, x, y), _text(text)
{
}

void TextWindow::redraw()
{
    const int textX = width() / 2 + static_cast<int>(_text.length()) / 2 - 2;
    const int textY = height() / 2;
    Window::redraw();
    printAt(textX, textY, _text);
}