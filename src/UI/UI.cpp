#include "UI.hpp"
#include "Figure.hpp"
#include <exception>

UI::UI(const std::array<Line, Config::linesCount>& lines)
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();

    initializeDoubleMachineFigures({
      lines.at(0).first,
      lines.at(1).first,
      lines.at(2).first,
      lines.at(3).first,
    });
}

UI::~UI()
{
    endwin();
}

void UI::initializeDoubleMachineFigures(const std::array<std::shared_ptr<DoubleMachine>, Config::linesCount>& machines)
{
    for (std::size_t i = 0; i < Config::linesCount; i++)
    {
        constexpr int offset = 1;
        constexpr int spacing = 14;
        constexpr int colIndex = 20;
        const int rowIndex = offset + static_cast<int>(i) * spacing;

        doubleMachineFigures.push_back(std::make_shared<DoubleMachineFigure>(rowIndex, colIndex, machines.at(i)));
    }
}

void UI::initializeSingleMachineFigures()
{
    for (int i = 0; i < Config::linesCount; i++)
    {
        constexpr int offset = 3;
        constexpr int spacing = 14;
        constexpr int colIndex = 110;
        const int rowIndex = offset + i * spacing;

        singleMachineFigures.push_back(std::make_shared<SingleMachineFigure>(rowIndex, colIndex));
    }
}

void UI::initializeHalfMachineFigures()
{
    for (int i = 0; i < Config::linesCount + 1; i++)
    {
        constexpr int offset = 14;
        constexpr int spacing = 6;
        constexpr int colIndex = 196;
        const int rowIndex = offset + i * spacing;
        bool hasStandBelow = true;

        if (i == Config::linesCount)
            hasStandBelow = false;

        halfMachineFigures.push_back(std::make_shared<HalfMachineFigure>(rowIndex, colIndex, hasStandBelow));
    }
}

std::shared_ptr<CarFigure> UI::createCarFigure()
{
    carFigures.push_back(std::make_shared<CarFigure>(10, 10));
    return carFigures.back();
}