#pragma once
#include "Line.hpp"
#include "Config.hpp"

class Factory
{
public:
    Factory();

private:
    std::array<Line, Config::linesCount> lines;

    void setupLines();
};