#pragma once
#include "Figure.hpp"
#include <memory>

class DoubleMachineFigure
{
public:
    DoubleMachineFigure(int rowIndex, int colIndex);

private:
    std::unique_ptr<Figure> machine;
    std::pair<std::unique_ptr<Figure>, std::unique_ptr<Figure>> stands;

    void initializeMachine(int rowIndex, int colIndex);
    void initializeStands(int rowIndex, int colIndex);
};