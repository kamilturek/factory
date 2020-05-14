#include "Factory.hpp"
#include "DoubleMachine.hpp"
#include "HalfMachine.hpp"
#include "SingleMachine.hpp"
#include <iostream>
#include <memory>

Factory::Factory() :
    _carScheduler(&Factory::scheduleCars, this),
    _carCollector(&Factory::collectCars, this)
{
    setupLines();
}

Factory::~Factory()
{
    _carCollector.join();
    _carScheduler.join();
}

int Factory::completedCars() const
{
    return _completedCars;
}

bool Factory::isWorking() const
{
    return _isWorking;
}

void Factory::setWorking(bool value)
{
    _isWorking = value;
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

const std::array<Line, Config::linesCount>& Factory::getLines() const
{
    return _lines;
}

const std::vector<std::shared_ptr<Car>>& Factory::cars() const
{
    return _cars;
}

void Factory::scheduleCars()
{
    while (_isWorking)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // CONSIDER USAGE OF CONDITION VARIABLE
        std::lock_guard<std::mutex> lock(carsMutex);
        if (_cars.size() < 20)
        {
            const auto lineNumber = static_cast<std::size_t>(_random.randomInt(0, Config::linesCount - 1));
            const Line& line = _lines.at(lineNumber);
            const int color = _random.randomInt(COLOR_RED, COLOR_CYAN);

            _cars.push_back(std::make_shared<Car>(line, color, _isWorking));
        }
    }
}

void Factory::collectCars()
{
    while (_isWorking)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // CONSIDER USAGE OF CONDITION VARIABLE
        std::lock_guard<std::mutex> lock(carsMutex);
        const auto completedBegin = std::remove_if(_cars.begin(), _cars.end(), [](const auto& car) { return car->state() == State::FINISHED; });
        _completedCars += static_cast<int>(std::distance(completedBegin, _cars.end()));
        _cars.erase(completedBegin, _cars.end());
    }

    std::lock_guard<std::mutex> lock(carsMutex);
    _cars.erase(_cars.begin(), _cars.end());
}