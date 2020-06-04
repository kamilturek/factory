#include "Conservator.hpp"

Conservator::Conservator(int x, int y) : _x(x), _y(y), _figure(std::make_shared<Window>(10, 5, _x, _y))
{

}

std::shared_ptr<Window> Conservator::figure() const
{
    return _figure;
}