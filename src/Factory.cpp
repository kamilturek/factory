#include "Factory.hpp"
#include "DoubleMachine.hpp"
#include "HalfMachine.hpp"
#include "SingleMachine.hpp"
#include <iostream>
#include <memory>

Factory::Factory(int carsNumber, int scheduleInterval, int collectionInterval) :
    _state(std::make_shared<FactoryState>(true)),
    _cars(std::make_shared<MutexVector<std::shared_ptr<Car>>>()),
    _carsNumber(carsNumber),
    _scheduleTimestamp(std::chrono::system_clock::now()),
    _collectTimestamp(std::chrono::system_clock::now()),
    _collectorCv(std::make_shared<std::condition_variable>()),
    _scheduleInterval(scheduleInterval),
    _collectionInterval(collectionInterval),
    _carScheduler(&Factory::scheduleCars, this),
    _carCollector(&Factory::collectCars, this),
    _machineInspector(&Factory::inspectMachines, this)
{
    setupLines();
    setupBrokenMachinesQueue();
    setupConservators();
}

Factory::~Factory()
{
    _machineInspector.join();
    _carCollector.join();
    _carScheduler.join();
    endwin();
}

int Factory::completedCars() const
{
    return _completedCars;
}

void Factory::run()
{
    _state->isWorking = true;
}

void Factory::stop()
{
    _state->isWorking = false;
}

void Factory::setupLines()
{
    _lines.at(0).number = 0;
    _lines.at(0).first = std::make_shared<DoubleMachine>();
    _lines.at(0).second = std::make_shared<SingleMachine>();
    _lines.at(0).thirdOne = std::make_shared<HalfMachine>();
    _lines.at(0).thirdTwo = std::make_shared<HalfMachine>();

    _lines.at(1).number = 1;
    _lines.at(1).first = std::make_shared<DoubleMachine>();
    _lines.at(1).second = std::make_shared<SingleMachine>();
    _lines.at(1).thirdOne = _lines.at(0).thirdTwo;
    _lines.at(1).thirdTwo = std::make_shared<HalfMachine>();

    _lines.at(2).number = 2;
    _lines.at(2).first = std::make_shared<DoubleMachine>();
    _lines.at(2).second = std::make_shared<SingleMachine>();
    _lines.at(2).thirdOne = _lines.at(1).thirdTwo;
    _lines.at(2).thirdTwo = std::make_shared<HalfMachine>();

    _lines.at(3).number = 3;
    _lines.at(3).first = std::make_shared<DoubleMachine>();
    _lines.at(3).second = std::make_shared<SingleMachine>();
    _lines.at(3).thirdOne = _lines.at(2).thirdTwo;
    _lines.at(3).thirdTwo = std::make_shared<HalfMachine>();
}

void Factory::setupBrokenMachinesQueue()
{
    _brokenMachines = std::make_shared<SafeQueue<std::shared_ptr<Machine>>>();
}

void Factory::setupConservators()
{
    const std::array<std::tuple<int, int, std::string>, 4> conservatorData{{
        { 190, 47, "Bob" },
        { 201, 47, "Tom" },
        { 212, 47, "Dan" },
        { 223, 47, "Gus" }
    }};


    for (std::size_t i = 0; i < conservatorData.size(); i++)
    {
        const auto data = conservatorData.at(i);
        _conservators.push_back(std::make_shared<Conservator>(std::get<0>(data), std::get<1>(data), std::get<2>(data), _state, _brokenMachines));
    }
}

const std::array<Line, Config::linesCount>& Factory::getLines() const
{
    return _lines;
}

std::shared_ptr<const FactoryState> Factory::state() const
{
    return _state;
}

const std::shared_ptr<MutexVector<std::shared_ptr<Car>>>& Factory::cars() const
{
    return _cars;
}

const std::vector<std::shared_ptr<Conservator>>& Factory::conservators() const
{
    return _conservators;
}

void Factory::scheduleCars()
{
    while (_state->isWorking)
    {
        {
            std::lock_guard<std::mutex> lock(_cars->mutex);
            _scheduleTimestamp = std::chrono::system_clock::now();
            if (_cars->size() < 35)
            {
                for (int i = 0; i < _carsNumber; i++)
                {
                    const auto lineNumber = static_cast<std::size_t>(_random.randomInt(0, Config::linesCount - 1));
                    const Line& line = _lines.at(lineNumber);
                    const int color = _random.randomInt(COLOR_RED, COLOR_CYAN);

                    _cars->push_back(std::make_shared<Car>(line, color, _state, _collectorCv));
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(_scheduleInterval));
    }
}

void Factory::collectCars()
{
    while (_state->isWorking)
    {
        std::unique_lock<std::mutex> lock(_cars->mutex);
        _collectorCv->wait(lock, [&]()
        {
            return std::any_of(_cars->begin(), _cars->end(), [](const auto& car)
            {
                return car->state() == State::FINISHED;
            });
        });
        _collectTimestamp = std::chrono::system_clock::now();
        const auto completedBegin = std::remove_if(_cars->begin(), _cars->end(), [](const auto& car) { return car->state() == State::FINISHED; });
        _completedCars += static_cast<int>(std::distance(completedBegin, _cars->end()));
        _cars->erase(completedBegin, _cars->end());
    }

    std::lock_guard<std::mutex> lock(_cars->mutex);
    _cars->erase(_cars->begin(), _cars->end());
}

void Factory::inspectMachines()
{
    while (_state->isWorking)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        for (const auto& line : _lines)
            for (const auto& machine : line.machines())
                if (machine->condition == 0)
                    _brokenMachines->push(machine);
    }
}

int Factory::nextSchedule() const
{
    return _scheduleInterval - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _scheduleTimestamp).count();
}

int Factory::nextCollect() const
{
    return _collectionInterval - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _collectTimestamp).count();
}