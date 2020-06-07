#include "Collector.hpp"

Collector::Collector(const std::shared_ptr<MutexVector<std::shared_ptr<Car>>>& cars) : _cars(cars), _thread(&Collector::work, this)
{
}

Collector::~Collector()
{
    _thread.join();
}

void work()
{

}