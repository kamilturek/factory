#pragma once
#include "CarFigure.hpp"
#include "Line.hpp"
#include "Random.hpp"
#include "State.hpp"
#include <atomic>
#include <thread>

class Car
{
public:
    explicit Car(const Line& line, int color, const std::atomic<bool>& isFactoryWorking);
    Car(const Car&) = delete;
    Car(Car&&) = delete;
    virtual ~Car();

    float progress() const;
    unsigned int line() const;
    State state() const;

    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&) = delete;

    std::shared_ptr<CarFigure> figure() const;

private:
    std::thread _thread;
    std::shared_ptr<CarFigure> _figure;
    const Line& _line;

    const int _color;

    const std::atomic<bool>& _isFactoryWorking;
    std::atomic<State> _state = State::WAITING;
    std::atomic<float> _progress = 0.0f;

    void assemble();
    void makeProgress(const std::vector<std::shared_ptr<Machine>>& currentMachines);
    void wearMachine(const std::vector<std::shared_ptr<Machine>>& currentMachines, int wear);
};