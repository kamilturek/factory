#include "Car.hpp"
#include "Config.hpp"

Car::Car(const Line& line, int color) :
    _thread(&Car::assemble, this),
    _figure(std::make_shared<CarFigure>(color)),
    _line(line),
    _color(color)
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

float Car::progress() const
{
    return _progress;
}

unsigned int Car::getLineNumber() const
{
    return _line.number;
}

State Car::state() const
{
    return _state;
}

void Car::assemble()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    _line.first->lock.acquire();
    _state = State::PHASE_ONE;

    makeProgress();

    _line.second->mutex.lock();
    _line.first->lock.release();
    _state = State::PHASE_TWO;

    makeProgress();

    {
        std::scoped_lock lock(_line.thirdOne->mutex, _line.thirdTwo->mutex);
        _state = State::PHASE_THREE;
        _line.second->mutex.unlock();

        makeProgress();

        _state = State::FINISHED;
    }
}

void Car::makeProgress()
{
    _progress = 0.0f;
    const int delayCount = Random().randomInt(15, 50);

    for (int i = 1; i <= delayCount; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        _progress = static_cast<float>(i) / static_cast<float>(delayCount);
    }
}