#pragma once
#include "Figure.hpp"
#include <memory>

class DoubleMachineFigure
{
public:
    DoubleMachineFigure(int rowIndex, int colIndex);

private:
    static constexpr int machineWidth   = 20;
    static constexpr int machineHeight  = 3;
    static constexpr int standWidth     = 18;
    static constexpr int standHeight    = 5;

    std::unique_ptr<Figure> machine;
    std::pair<std::unique_ptr<Figure>, std::unique_ptr<Figure>> stands;

    void initializeMachine(int rowIndex, int colIndex);
    void initializeStands(int rowIndex, int colIndex);
};