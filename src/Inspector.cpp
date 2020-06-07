#include "Inspector.hpp"

Inspector::Inspector(int x, int y, const std::string& name, const Line& line,
  const std::shared_ptr<const FactoryState>& factoryState,
  const std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>>& brokenMachines) :
    _x(x),
    _y(y),
    _startX(x),
    _startY(y),
    _line(line),
    _factoryState(factoryState),
    _brokenMachines(brokenMachines),
    _figure(std::make_shared<TextWindow>(9, 3, _x, _y, name)),
    _thread(&Inspector::work, this)
{
}

Inspector::~Inspector()
{
    _thread.join();
}

std::shared_ptr<TextWindow> Inspector::figure() const
{
    return _figure;
}

void Inspector::work()
{
    while (_factoryState->isWorking)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));

        for (const auto machine : _line.machines())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            _x = machine->x + 22;
            _y = machine->y + 4;

            if (machine->condition == 0)
                _brokenMachines->push(machine);
        }
        _x = _startX;
        _y = _startY;
    }
}

int Inspector::x() const
{
    return _x;
}

int Inspector::y() const
{
    return _y;
}