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
}

void UI::initializeDoubleMachineFigures()
{
    for (int i = 0; i < Config::linesCount; i++)
    {
        constexpr int offset = 1;
        constexpr int spacing = 14;
        const int rowIndex = offset + i * spacing;
        const int columnIndex = 5;

        figures.push_back(std::make_shared<DoubleMachineFigure>(rowIndex, columnIndex));
    }
}