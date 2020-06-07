#pragma once
#include "Car.hpp"
#include "Collector.hpp"
#include "Config.hpp"
#include "Conservator.hpp"
#include "FactoryState.hpp"
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
    const std::array<Line, Config::linesCount>& getLines() const;

    int nextSchedule() const;

private:
    const int _carsNumber;
    const int _scheduleInterval;
    const int _collectionInterval;

    std::atomic<int> _completedCars = 0;

    std::shared_ptr<FactoryState> _state;
    std::shared_ptr<MutexVector<std::shared_ptr<Car>>> _cars;
    std::shared_ptr<Collector> _collector;

    std::thread _carScheduler;
    std::thread _machineInspector;

    Random _random;


    std::array<Line, Config::linesCount> _lines;
    std::vector<std::shared_ptr<Conservator>> _conservators;
    std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>> _brokenMachines;

    std::chrono::time_point<std::chrono::system_clock> _scheduleTimestamp;

    void setupLines();
    void setupBrokenMachinesQueue();
    void setupConservators();
    void scheduleCars();
    void inspectMachines();
};