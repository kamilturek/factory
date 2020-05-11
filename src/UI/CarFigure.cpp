#include "CarFigure.hpp"
#include "Config.hpp"
#include <iostream>

CarFigure::CarFigure(std::shared_ptr<Car> car) :
    Figure(Config::carWidth,
      Config::carHeight,
      Config::invisible.first,
      Config::invisible.second,
      false),
    _car(std::move(car))
{
}

const std::shared_ptr<const Car> CarFigure::getCar() const
{
    return _car;
}