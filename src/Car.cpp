#include "Car.hpp"
#include "Config.hpp"

Car::Car(const Line& line, int color, const std::atomic<bool>& isFactoryWorking) :
    _thread(&Car::assemble, this),
    _figure(std::make_shared<CarFigure>(color)),
    _line(line),
    _color(color),
    _isFactoryWorking(isFactoryWorking)
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

    if (!_isFactoryWorking)
        return;

    // Double Machine
    std::unique_lock<CountingLock> doubleMachineLock(_line.first->lock);
    _state = State::PHASE_ONE;
    makeProgress();

    if (!_isFactoryWorking)
        return;

    // Single Machine
    std::unique_lock<std::mutex> singleMachineLock(_line.second->mutex);
    _state = State::PHASE_TWO;
    doubleMachineLock.unlock();
    makeProgress();

    if (!_isFactoryWorking)
        return;

    // Half Machine
    {
        std::scoped_lock lock(_line.thirdOne->mutex, _line.thirdTwo->mutex);
        _state = State::PHASE_THREE;
        singleMachineLock.unlock();
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
        if (!_isFactoryWorking)
            return;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        _progress = static_cast<float>(i) / static_cast<float>(delayCount);
    }
}