#pragma once
#include "Line.hpp"
#include "Config.hpp"

class Factory
{
public:
    Factory();

    const std::array<Line, Config::linesCount>& getLines() const;

private:
    std::array<Line, Config::linesCount> lines;

    void setupLines();
};