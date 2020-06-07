#pragma once
#include "Car.hpp"
#include "FactoryState.hpp"
#include "MutexVector.hpp"
#include <memory>
#include <thread>

class Collector
{
public:
    Collector(const std::shared_ptr<const FactoryState>& factoryState, const std::shared_ptr<MutexVector<std::shared_ptr<Car>>>& cars);
    ~Collector();

private:
    std::thread _thread;
    std::shared_ptr<const FactoryState> _factoryState;
    std::shared_ptr<MutexVector<std::shared_ptr<Car>>> _cars;

    void work();
};