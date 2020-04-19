#pragma once
#include "Line.hpp"

class Factory
{
public:
    Factory();

private:
    static constexpr unsigned int linesCount = 4;
    std::array<Line, linesCount> lines;

    void setupLines();
};