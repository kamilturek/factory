#include "Car.hpp"

Car::Car(const Line& line) : _state(State::WAITING), _thread(&Car::assemble, this), _line(line)
{
}

Car::~Car()
{
    _thread.join();
}

unsigned int Car::getLineNumber() const
{
    return _line.number;
}

State Car::getState() const
{
    return _state;
}

void Car::assemble()
{
}