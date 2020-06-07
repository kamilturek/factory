#include "Factory.hpp"
#include "DoubleMachine.hpp"
#include "HalfMachine.hpp"
#include "SingleMachine.hpp"
#include <iostream>
#include <memory>

Factory::Factory(int carsNumber, int scheduleInterval, int collectionInterval) :
    _state(std::make_shared<FactoryState>(true)),
    _cars(std::make_shared<MutexVector<std::shared_ptr<Car>>>()),
    _collector(std::make_shared<Collector>(_state, _cars)),
    _brokenMachines(std::make_shared<SafeQueue<std::shared_ptr<Machine>>>()),
    _carsNumber(carsNumber),
    _scheduleTimestamp(std::chrono::system_clock::now()),
    _scheduleInterval(scheduleInterval),
    _collectionInterval(collectionInterval),
    _carScheduler(&Factory::scheduleCars, this)
{
    setupLines();
    setupConservators();
    setupInspectors();
}

Factory::~Factory()
{
    _carScheduler.join();
    endwin();
}

unsigned int Factory::completedCars() const
{
    return _collector->collectedCount();
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

void Factory::setupInspectors()
{
    const std::array<std::tuple<int, int, std::string>, 4> inspectorData{{
        { 141, 47, "IN1" },
        { 152, 47, "IN2" },
        { 163, 47, "IN3" },
        { 174, 47, "IN4" }
    }};


    for (std::size_t i = 0; i < inspectorData.size(); i++)
    {
        const auto data = inspectorData.at(i);
        _inspectors.push_back(std::make_shared<Inspector>(std::get<0>(data), std::get<1>(data), std::get<2>(data), _lines.at(i), _state, _brokenMachines));
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

const std::vector<std::shared_ptr<Inspector>>& Factory::inspectors() const
{
    return _inspectors;
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

                    _cars->push_back(std::make_shared<Car>(line, color, _state, std::bind(&Collector::notify, _collector)));
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(_scheduleInterval));
    }
}

int Factory::nextSchedule() const
{
    return _scheduleInterval - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _scheduleTimestamp).count();
}