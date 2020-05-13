#pragma once
#include "Figure.hpp"
#include <memory>

class DoubleMachineFigure
{
public:
    DoubleMachineFigure(int rowIndex, int colIndex);

    void refresh();

    int getRowIndex() const;
    int getColIndex() const;

    bool upperPartTaken = false;

private:
    int _currRowIndex;
    int _currColIndex;

    std::unique_ptr<Figure> _machineFigure;
    std::pair<std::unique_ptr<Figure>, std::unique_ptr<Figure>> _standFigures;

    void initializeMachine(int rowIndex, int colIndex);
    void initializeStands(int rowIndex, int colIndex);
};