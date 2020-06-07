#pragma once
#include "Car.hpp"
#include "Config.hpp"
#include "Conservator.hpp"
#include "Line.hpp"
#include "Random.hpp"
#include "SafeQueue.hpp"
#include <thread>

class Factory
{
public:
    Factory(int carsNumber, int scheduleInterval, int collectionInterval);
    ~Factory();

    int completedCars() const;
    bool isWorking() const;
    void setWorking(bool value);

    std::mutex carsMutex;
    const std::vector<std::shared_ptr<Car>>& cars() const;
    const std::vector<std::shared_ptr<Conservator>>& conservators() const;
    const std::array<Line, Config::linesCount>& getLines() const;

    int nextSchedule() const;
    int nextCollect() const;


private:
    const int _carsNumber;
    const int _scheduleInterval;
    const int _collectionInterval;

    std::atomic<bool> _isWorking = true;
    std::atomic<int> _completedCars = 0;
    
    std::shared_ptr<std::condition_variable> _collectorCv;

    std::thread _carScheduler;
    std::thread _carCollector;
    std::thread _machineInspector;

    Random _random;


    std::array<Line, Config::linesCount> _lines;
    std::vector<std::shared_ptr<Car>> _cars;
    std::vector<std::shared_ptr<Conservator>> _conservators;
    std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>> _brokenMachines;

    std::chrono::time_point<std::chrono::system_clock> _scheduleTimestamp;
    std::chrono::time_point<std::chrono::system_clock> _collectTimestamp;


    void setupLines();
    void setupBrokenMachinesQueue();
    void setupConservators();
    void scheduleCars();
    void collectCars();
    void inspectMachines();
};