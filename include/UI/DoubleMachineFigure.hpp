#pragma once
#include "DoubleMachine.hpp"
#include "Figure.hpp"
#include <memory>

class DoubleMachineFigure
{
public:
    DoubleMachineFigure(int rowIndex, int colIndex, std::shared_ptr<DoubleMachine> machine);

private:
    std::shared_ptr<DoubleMachine> _machine;
    std::unique_ptr<Figure> _machineFigure;
    std::pair<std::unique_ptr<Figure>, std::unique_ptr<Figure>> _standFigures;

    void initializeMachine(int rowIndex, int colIndex);
    void initializeStands(int rowIndex, int colIndex);
};