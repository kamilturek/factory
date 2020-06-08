#pragma once
#include "Window.hpp"
#include <memory>
#include <string>

class TextWindow : public Window
{
public:
    TextWindow(int width, int height, int x, int y, const std::string& text, bool reversed = false);

    void redraw() override;
    void moveTo(int x, int y);
    void reset();

private:
    std::string _text;
    bool _reversed;
};