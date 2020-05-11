#pragma once
#include "Car.hpp"
#include "Config.hpp"
#include "Line.hpp"
#include "Queue.hpp"
#include "Random.hpp"

class Factory
{
public:
    Factory();

    const std::array<Line, Config::linesCount>& getLines() const;
    std::shared_ptr<Queue<std::shared_ptr<Car>>> getCars();

    void createCar();

private:
    std::array<Line, Config::linesCount> _lines;
    std::shared_ptr<Queue<std::shared_ptr<Car>>> _cars;
    Random random;

    void setupLines();
};