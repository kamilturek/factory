#pragma once
#include "Line.hpp"
#include "State.hpp"
#include "Position.hpp"
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

    Position position = Position::UNDEFINED;

    std::unique_ptr<Figure> _figure;
private:
    static constexpr int width = 15;
    static constexpr int height = 4;

    State _state;


    std::thread _thread;
    const Line& _line;

    void assemble();
};