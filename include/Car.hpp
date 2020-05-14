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
    explicit Car(const Line& line, int color);
    Car(const Car&) = delete;
    Car(Car&&) = delete;
    virtual ~Car();

    float progress() const;

    unsigned int getLineNumber() const;
    State getState() const;

    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&) = delete;

    std::shared_ptr<CarFigure> figure() const;

private:
    std::thread _thread;
    std::shared_ptr<CarFigure> _figure;
    std::atomic<State> _state;
    const Line& _line;

    const int _color;
    std::atomic<float> _progress;

    void assemble();
    void makeProgress();
};