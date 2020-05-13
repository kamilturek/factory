#include "DoubleMachineFigure.hpp"
#include "Config.hpp"

DoubleMachineFigure::DoubleMachineFigure(int rowIndex, int colIndex) : _currRowIndex(rowIndex), _currColIndex(colIndex) 
{
    initializeStands(rowIndex, colIndex);
    initializeMachine(rowIndex, colIndex);
}

void DoubleMachineFigure::initializeMachine(int rowIndex, int colIndex)
{
    _machineFigure = std::make_unique<Figure>(Config::machineWidth, Config::machineHeight, rowIndex + Config::standHeight, colIndex, true);
}

void DoubleMachineFigure::initializeStands(int rowIndex, int colIndex)
{
    constexpr int offset = 1;
    _standFigures.first = std::make_unique<Figure>(Config::standWidth, Config::standHeight, rowIndex + offset, colIndex + offset, true);
    _standFigures.second = std::make_unique<Figure>(Config::standWidth, Config::standHeight, rowIndex + Config::standHeight + Config::machineHeight - offset, colIndex + offset, true);
}

void DoubleMachineFigure::refresh()
{
    _standFigures.first->erase();
    _standFigures.first->draw();
    _standFigures.second->erase();
    _standFigures.second->draw();
    _machineFigure->erase();
    _machineFigure->draw();
}

int DoubleMachineFigure::getRowIndex() const
{
    return _currRowIndex;
}

int DoubleMachineFigure::getColIndex() const
{
    return _currColIndex;
}