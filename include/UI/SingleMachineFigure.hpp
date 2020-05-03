#pragma once
#include "Figure.hpp"
#include <memory>

class SingleMachineFigure
{
public:
    SingleMachineFigure(int rowIndex, int colIndex);

private:
    static constexpr int machineWidth   = 20;
    static constexpr int machineHeight  = 3;
    static constexpr int standWidth     = 18;
    static constexpr int standHeight    = 5;

    std::unique_ptr<Figure> machine;
    std::unique_ptr<Figure> stand;

    void initializeMachine(int rowIndex, int colIndex);
    void initializeStand(int rowIndex, int colIndex);
};