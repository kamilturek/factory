#pragma once
#include "Car.hpp"
#include "Config.hpp"
#include "Line.hpp"
#include "Random.hpp"
#include <thread>

class Factory
{
public:
    Factory();
    ~Factory();

    bool isWorking() const;
    const std::array<Line, Config::linesCount>& getLines() const;
    const std::vector<std::unique_ptr<Car>>& getCars() const;

    void setWorking(bool value);

    std::mutex carCollectionMutex;

private:
    bool _isWorking;
    std::thread _carScheduler;
    std::thread _carCollector;

    Random _random;

    std::array<Line, Config::linesCount> _lines;
    std::vector<std::unique_ptr<Car>> _cars;

    void setupLines();
    void scheduleCars();
    void collectCars();
};