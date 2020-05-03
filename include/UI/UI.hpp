#include "ncurses.h"

class UI
{
public:
    UI();
    UI(const UI&) = default;
    UI(UI&&) = default;
    ~UI();

    UI& operator=(const UI&) = default;
    UI& operator=(UI&&) = default;
};