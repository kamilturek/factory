#pragma once
#include "Car.hpp"
#include "Config.hpp"
#include "Line.hpp"
#include "Random.hpp"

class Factory
{
public:
    Factory();

    bool isWorking() const;
    const std::array<Line, Config::linesCount>& getLines() const;
    const std::vector<std::unique_ptr<Car>>& getCars() const;

    void setWorking(bool value);
    void createCar();

private:
    bool _isWorking;
    Random random;

    std::array<Line, Config::linesCount> _lines;
    std::vector<std::unique_ptr<Car>> _cars;

    void setupLines();
};