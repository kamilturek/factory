#pragma once
#include "Line.hpp"
#include "State.hpp"
#include "CarFigure.hpp"
#include <atomic>
#include <thread>

class Car
{
public:
    explicit Car(const Line& line);
    Car(const Car&) = delete;
    Car(Car&&) = delete;
    virtual ~Car();

    unsigned int getLineNumber() const;
    State getState() const;

    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&) = delete;

    std::shared_ptr<CarFigure> figure() const;

private:
    std::thread _thread;
    std::shared_ptr<CarFigure> _figure;
    State _state;
    const Line& _line;

    void assemble();
};