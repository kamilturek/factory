#pragma once
#include <memory>
#include "Window.hpp"

class Conservator
{
public:
    Conservator(int x, int y);

    std::shared_ptr<Window> figure() const;

private:
    const int _x;
    const int _y;

    std::shared_ptr<Window> _figure;
};