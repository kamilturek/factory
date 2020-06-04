#pragma once
#include <memory>
#include "TextWindow.hpp"

class Conservator
{
public:
    Conservator(int x, int y, const std::string& name);

    std::shared_ptr<TextWindow> figure() const;

private:
    const int _x;
    const int _y;

    std::shared_ptr<TextWindow> _figure;
};