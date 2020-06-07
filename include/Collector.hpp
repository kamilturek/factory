#pragma once
#include "Car.hpp"
#include "FactoryState.hpp"
#include "MutexVector.hpp"
#include <condition_variable>
#include <memory>
#include <thread>

class Collector
{
public:
    Collector(const std::shared_ptr<const FactoryState>& factoryState, const std::shared_ptr<MutexVector<std::shared_ptr<Car>>>& cars);
    ~Collector();

    void notify();
    unsigned int collectedCount() const;

private:
    std::shared_ptr<const FactoryState> _factoryState;
    std::shared_ptr<MutexVector<std::shared_ptr<Car>>> _cars;

    std::thread _thread;
    std::condition_variable _cv;

    std::atomic<unsigned int> _collectedCount;


    void work();
    void eraseCars();
};