#pragma once
#include "DoubleMachineFigure.hpp"
#include <memory>
#include <ncurses.h>
#include <vector>

class UI
{
public:
    UI();
    UI(const UI&) = default;
    UI(UI&&) = default;
    ~UI();

    UI& operator=(const UI&) = default;
    UI& operator=(UI&&) = default;

private:
    std::vector<std::shared_ptr<DoubleMachineFigure>> figures;

    void initializeMachineFigures();
    void initializeDoubleMachineFigures();
};