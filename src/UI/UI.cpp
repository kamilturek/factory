#include "UI.hpp"
#include "Config.hpp"
#include "Figure.hpp"

UI::UI()
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();

    initializeMachineFigures();
    getch();
}

UI::~UI()
{
    endwin();
}

void UI::initializeMachineFigures()
{
    initializeDoubleMachineFigures();
    initializeSingleMachineFigures();
    initializeHalfMachineFigures();
}

void UI::initializeDoubleMachineFigures()
{
    for (int i = 0; i < Config::linesCount; i++)
    {
        constexpr int offset = 1;
        constexpr int spacing = 14;
        constexpr int colIndex = 5;
        const int rowIndex = offset + i * spacing;

        doubleMachineFigures.push_back(std::make_shared<DoubleMachineFigure>(rowIndex, colIndex));
    }
}

void UI::initializeSingleMachineFigures()
{
    for (int i = 0; i < Config::linesCount; i++)
    {
        constexpr int offset = 3;
        constexpr int spacing = 14;
        constexpr int colIndex = 30;
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
        constexpr int colIndex = 55;
        const int rowIndex = offset + i * spacing;
        bool hasStandBelow = true;

        if (i == Config::linesCount)
            hasStandBelow = false;

        halfMachineFigures.push_back(std::make_shared<HalfMachineFigure>(rowIndex, colIndex, hasStandBelow));
    }
}