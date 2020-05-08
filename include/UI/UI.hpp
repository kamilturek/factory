#pragma once
#include "CarFigure.hpp"
#include "DoubleMachineFigure.hpp"
#include "HalfMachineFigure.hpp"
#include "SingleMachineFigure.hpp"
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
    std::vector<std::shared_ptr<DoubleMachineFigure>> doubleMachineFigures;
    std::vector<std::shared_ptr<SingleMachineFigure>> singleMachineFigures;
    std::vector<std::shared_ptr<HalfMachineFigure>> halfMachineFigures;
    std::vector<std::shared_ptr<CarFigure>> carFigures;

    void initializeMachineFigures();
    void initializeDoubleMachineFigures();
    void initializeSingleMachineFigures();
    void initializeHalfMachineFigures();
};