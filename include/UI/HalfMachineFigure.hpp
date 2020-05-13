#pragma once
#include "Figure.hpp"
#include <memory>

class HalfMachineFigure
{
public:
    HalfMachineFigure(int rowIndex, int colIndex, bool hasStand);

    int getRowIndex() const;
    int getColIndex() const;

private:
    int _currRowIndex;
    int _currColIndex;

    std::unique_ptr<Figure> machine;
    std::unique_ptr<Figure> stand;

    void initializeMachine(int rowIndex, int colIndex);
    void initializeStand(int rowIndex, int colIndex);
};