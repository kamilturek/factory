#pragma once
#include "Car.hpp"
#include "Config.hpp"
#include "Line.hpp"
#include "Random.hpp"
#include <thread>

class Factory
{
public:
    Factory(int carsNumber, int scheduleInterval, int collectionInterval);
    ~Factory();

    bool isWorking() const;
    void setWorking(bool value);

    std::mutex carsMutex;
    const std::vector<std::shared_ptr<Car>>& cars() const;
    const std::array<Line, Config::linesCount>& getLines() const;

    int completedCars() const;

private:
    const int _carsNumber;
    const int _scheduleInterval;
    const int _collectionInterval;

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