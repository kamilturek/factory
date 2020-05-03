#pragma once
#include "Figure.hpp"
#include <memory>

class SingleMachineFigure
{
public:
    SingleMachineFigure(int rowIndex, int colIndex);

private:
    std::unique_ptr<Figure> machine;
    std::unique_ptr<Figure> stand;

    void initializeMachine(int rowIndex, int colIndex);
    void initializeStand(int rowIndex, int colIndex);
};