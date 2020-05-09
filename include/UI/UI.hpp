#pragma once
#include "CarFigure.hpp"
#include "Config.hpp"
#include "DoubleMachine.hpp"
#include "DoubleMachineFigure.hpp"
#include "HalfMachineFigure.hpp"
#include "SingleMachineFigure.hpp"
#include <array>
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

    void initializeDoubleMachineFigures(const std::array<DoubleMachine, Config::linesCount>& machines);

    UI& operator=(const UI&) = default;
    UI& operator=(UI&&) = default;

private:
    std::vector<std::shared_ptr<DoubleMachineFigure>> doubleMachineFigures;
    std::vector<std::shared_ptr<SingleMachineFigure>> singleMachineFigures;
    std::vector<std::shared_ptr<HalfMachineFigure>> halfMachineFigures;
    std::vector<std::shared_ptr<CarFigure>> carFigures;

    void initializeMachineFigures();
    void initializeSingleMachineFigures();
    void initializeHalfMachineFigures();
    std::shared_ptr<CarFigure> createCarFigure();
};