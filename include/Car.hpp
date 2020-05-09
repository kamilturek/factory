#pragma once
#include "Line.hpp"
#include "State.hpp"
#include <thread>

class Car
{
public:
    explicit Car(const Line& line);
    Car(const Car&) = delete;
    Car(Car&&) = delete;
    virtual ~Car();

    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&) = delete;

private:
    State _state;
    std::thread _thread;
    const Line& _line;

    void assemble();
};