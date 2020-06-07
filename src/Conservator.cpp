#include "Conservator.hpp"
#include <iostream>

Conservator::Conservator(int x, int y, const std::string& name,
  const std::atomic<bool>& isFactoryWorking,
  const std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>>& brokenMachines) :
    _x(x),
    _y(y), _startX(x), _startY(y), _isFactoryWorking(isFactoryWorking), _thread(&Conservator::work, this), _figure(std::make_shared<TextWindow>(9, 3, _x, _y, name)), _brokenMachines(brokenMachines)
{
}

Conservator::~Conservator()
{
    _thread.join();
}

std::shared_ptr<TextWindow> Conservator::figure() const
{
    return _figure;
}

void Conservator::work()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (_isFactoryWorking)
    {
        const auto& machine = _brokenMachines->pop();
        std::lock_guard<std::mutex> lock(machine->conservationMutex);
        _x = machine->x + 22;
        _y = machine->y + 1;
        fixMachine(machine);
        _x = _startX;
        _y = _startY;
    }
}

void Conservator::fixMachine(const std::shared_ptr<Machine>& machine)
{
    const int progressPerStep = Random().randomInt(5, 15);

    while (machine->condition < 100)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(350));

        if (machine->condition + progressPerStep > 100)
            machine->condition = 100;
        else
            machine->condition += progressPerStep;
    }
}

int Conservator::x() const
{
    return _x;
}

int Conservator::y() const
{
    return _y;
}