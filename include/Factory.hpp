#pragma once
#include "Car.hpp"
#include "Config.hpp"
#include "Line.hpp"
#include "Random.hpp"
#include <queue>

class Factory
{
public:
    Factory();

    const std::array<Line, Config::linesCount>& getLines() const;
    std::pair<std::queue<std::shared_ptr<Car>>, std::mutex>& getCars();

    void createCar();

private:
    std::array<Line, Config::linesCount> _lines;
    std::pair<std::queue<std::shared_ptr<Car>>, std::mutex> _cars;
    Random random;

    void setupLines();
};