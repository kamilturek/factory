#include "Car.hpp"
#include "Config.hpp"

Car::Car(const Line& line, int color) :
    _thread(&Car::assemble, this),
    _figure(std::make_shared<CarFigure>(color)),
    _state(State::WAITING),
    _line(line)
{
}

Car::~Car()
{
    _thread.join();
}

std::shared_ptr<CarFigure> Car::figure() const
{
    return _figure;
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