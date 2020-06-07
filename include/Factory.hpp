#pragma once
#include "Car.hpp"
#include "Collector.hpp"
#include "Config.hpp"
#include "Conservator.hpp"
#include "FactoryState.hpp"
#include "Inspector.hpp"
#include "Line.hpp"
#include "MutexVector.hpp"
#include "Random.hpp"
#include "SafeQueue.hpp"
#include <functional>
#include <thread>

class Factory
{
public:
    Factory(int carsNumber, int scheduleInterval, int collectionInterval);
    ~Factory();

    unsigned int completedCars() const;

    void run();
    void stop();

    std::shared_ptr<const FactoryState> state() const;
    const std::shared_ptr<MutexVector<std::shared_ptr<Car>>>& cars() const;
    const std::vector<std::shared_ptr<Conservator>>& conservators() const;
    const std::vector<std::shared_ptr<Inspector>>& inspectors() const;
    const std::array<Line, Config::linesCount>& getLines() const;

    int nextSchedule() const;

private:
    const int _carsNumber;
    const int _scheduleInterval;
    const int _collectionInterval;

    std::shared_ptr<FactoryState> _state;
    std::shared_ptr<MutexVector<std::shared_ptr<Car>>> _cars;
    std::shared_ptr<Collector> _collector;
    std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>> _brokenMachines;

    std::thread _carScheduler;

    Random _random;

    std::array<Line, Config::linesCount> _lines;
    std::vector<std::shared_ptr<Conservator>> _conservators;
    std::vector<std::shared_ptr<Inspector>> _inspectors;

    std::chrono::time_point<std::chrono::system_clock> _scheduleTimestamp;

    void setupLines();
    void setupConservators();
    void setupInspectors();
    void scheduleCars();
};