#include "DoubleMachineFigure.hpp"
#include "Config.hpp"

DoubleMachineFigure::DoubleMachineFigure(int rowIndex, int colIndex, std::shared_ptr<DoubleMachine> machine) : _machine(std::move(machine))
{
    if (_machine == nullptr)
        throw std::logic_error("Machine does not exist.");
    
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