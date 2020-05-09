#include "Car.hpp"

Car::Car(const Line& line) : _state(State::WAITING), _thread(&Car::assemble, this), _line(line)
{
}

Car::~Car()
{
    _thread.join();
}

void Car::assemble()
{
}