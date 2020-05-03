#pragma once
#include "Figure.hpp"
#include <memory>

class HalfMachineFigure
{
public:
    HalfMachineFigure(int rowIndex, int colIndex, bool hasStand);

private:
    std::unique_ptr<Figure> machine;
    std::unique_ptr<Figure> stand;

    void initializeMachine(int rowIndex, int colIndex);
    void initializeStand(int rowIndex, int colIndex);
};