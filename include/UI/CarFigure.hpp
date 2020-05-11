#include "Car.hpp"
#include "Figure.hpp"
#include <memory>

class CarFigure : public Figure
{
public:
    CarFigure(std::shared_ptr<Car> car);

    const std::shared_ptr<const Car> getCar() const;

private:
    std::shared_ptr<Car> _car;
};