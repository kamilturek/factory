#include "Car.hpp"
#include "Config.hpp"
#include <exception>

Car::Car(const Line& line, int color, const std::shared_ptr<const FactoryState>& factoryState, std::function<void()> notifier) :
    _factoryState(factoryState),
    _notifier(notifier),
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

unsigned int Car::line() const
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

    if (!_factoryState->isWorking)
        return;

    // Double Machine
    std::unique_lock<CountingMutex> doubleMachineLock(_line.first->lock);
    _state = State::PHASE_ONE;
    makeProgress({ _line.first });

    if (!_factoryState->isWorking)
        return;

    // Single Machine
    std::unique_lock<std::mutex> singleMachineLock(_line.second->mutex);
    _state = State::PHASE_TWO;
    doubleMachineLock.unlock();
    makeProgress({ _line.second });

    if (!_factoryState->isWorking)
        return;

    // Half Machine
    {
        std::scoped_lock lock(_line.thirdOne->mutex, _line.thirdTwo->mutex);
        _state = State::PHASE_THREE;
        singleMachineLock.unlock();
        makeProgress({ _line.thirdOne, _line.thirdTwo });

        _state = State::FINISHED;
        _notifier();
    }
}

void Car::makeProgress(const std::vector<std::shared_ptr<Machine>>& currentMachines)
{
    _progress = 0.0f;
    const int delayCount = Random().randomInt(15, 50);
    constexpr int wearDegree = 2;

    for (int i = 1; i <= delayCount; i++)
    {
        while (_factoryState->isWorking && std::any_of(currentMachines.begin(), currentMachines.end(), [](const auto& machine) {
            return machine->condition == 0;
        }))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        };

        if (!_factoryState->isWorking)
            return;

        if (currentMachines.size() == 1)
        {
            std::lock_guard<std::mutex> lock(currentMachines.front()->conservationMutex);
            if (i % 2)
                wearMachine(currentMachines, wearDegree);
        }
        else if (currentMachines.size() == 2)
        {
            std::scoped_lock lock(currentMachines.front()->conservationMutex, currentMachines.back()->conservationMutex);
            if (i % 2)
                wearMachine(currentMachines, wearDegree);
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        _progress = static_cast<float>(i) / static_cast<float>(delayCount);
    }
}

void Car::wearMachine(const std::vector<std::shared_ptr<Machine>>& currentMachines, int wear)
{
    for (const auto& machine : currentMachines)
    {
        if (machine->condition < wear)
            machine->condition = 0;
        else
            machine->condition -= wear;
    }
}