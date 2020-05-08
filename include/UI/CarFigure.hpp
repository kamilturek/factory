#include "Figure.hpp"
#include <memory>

class CarFigure
{
public:
    CarFigure(int rowIndex, int colIndex);

private:
    std::unique_ptr<Figure> figure;
};