#include "Collector.hpp"

Collector::Collector(const std::shared_ptr<const FactoryState>& factoryState, const std::shared_ptr<MutexVector<std::shared_ptr<Car>>>& cars) :
    _factoryState(factoryState), _cars(cars), _thread(&Collector::work, this), _collectedCount(0)
{
}

Collector::~Collector()
{
    _thread.join();
}

void Collector::notify()
{
    _cv.notify_one();
}

unsigned int Collector::collectedCount() const
{
    return _collectedCount;
}

void Collector::work()
{
    while (_factoryState->isWorking)
    {
        std::unique_lock<std::mutex> lock(_cars->mutex);
        _cv.wait(lock, [&]()
        {
            return std::any_of(_cars->begin(), _cars->end(), [](const auto car) { return car->state() == State::FINISHED; });
        });
        const auto begin = std::remove_if(_cars->begin(), _cars->end(), [](const auto car) { return car->state() == State::FINISHED; });
        _collectedCount += static_cast<unsigned int>(std::distance(begin, _cars->end()));
        _cars->erase(begin, _cars->end());
    }

    eraseCars();
}

void Collector::eraseCars()
{
    std::lock_guard<std::mutex> lock(_cars->mutex);
    _cars->erase(_cars->begin(), _cars->end());
}