#include "Car.hpp"
#include "Config.hpp"

Car::Car(const Line& line) :
    _state(State::WAITING),
    _thread(&Car::assemble, this),
    _line(line),
    _figure(std::make_unique<Figure>(width, height, -99, -99, true))
{
}

Car::~Car()
{
    _thread.join();
}

unsigned int Car::getLineNumber() const
{
    return _line.number;
}

State Car::getState() const
{
    return _state;
}

void Car::assemble()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    _line.first->lock.acquire();
    _state = State::PHASE_ONE;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    _line.second->mutex.lock();
    _line.first->lock.release();
    _state = State::PHASE_TWO;

    std::this_thread::sleep_for(std::chrono::seconds(6));

    {
        std::scoped_lock lock(_line.thirdOne->mutex, _line.thirdTwo->mutex);
        _state = State::PHASE_THREE;
        _line.second->mutex.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(4));
        _state = State::FINISHED;
    }
}