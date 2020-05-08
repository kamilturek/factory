#include "CarFigure.hpp"
#include "Config.hpp"

CarFigure::CarFigure(int rowIndex, int colIndex)
{
    figure = std::make_unique<Figure>(Config::carWidth, Config::carHeight, rowIndex, colIndex, true);
}