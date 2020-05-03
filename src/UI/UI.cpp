#include "UI.hpp"

UI::UI()
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();

    printw("Hello world!");
    getch();
}

UI::~UI()
{
    endwin();
}