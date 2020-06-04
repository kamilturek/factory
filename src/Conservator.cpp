#include "Conservator.hpp"

Conservator::Conservator(int x, int y, const std::string& name) : _x(x), _y(y), _figure(std::make_shared<TextWindow>(9, 3, _x, _y, name))
{

}

std::shared_ptr<TextWindow> Conservator::figure() const
{
    return _figure;
}