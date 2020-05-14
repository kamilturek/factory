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

    void setWorking(bool value);

    std::mutex carsMutex;
    const std::vector<std::shared_ptr<Car>>& cars() const;

    int completedCars() const;

private:
    std::atomic<bool> _isWorking = true;
    std::atomic<int> _completedCars = 0;

    std::thread _carScheduler;
    std::thread _carCollector;

    Random _random;


    std::array<Line, Config::linesCount> _lines;
    std::vector<std::shared_ptr<Car>> _cars;

    void setupLines();
    void scheduleCars();
    void collectCars();
};