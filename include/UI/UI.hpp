#pragma once
#include "Car.hpp"
#include "CarFigure.hpp"
#include "Config.hpp"
#include "DoubleMachine.hpp"
#include "DoubleMachineFigure.hpp"
#include "HalfMachineFigure.hpp"
#include "Line.hpp"
#include "Queue.hpp"
#include "SingleMachineFigure.hpp"
#include <array>
#include <memory>
#include <ncurses.h>
#include <vector>

class UI
{
public:
    UI(const std::array<Line, Config::linesCount>& lines, std::shared_ptr<Queue<std::shared_ptr<Car>>> cars);
    UI(const UI&) = delete;
    UI(UI&&) = delete;
    ~UI();

    UI& operator=(const UI&) = delete;
    UI& operator=(UI&&) = delete;

private:
    std::thread _viewThread;

    std::vector<std::shared_ptr<DoubleMachineFigure>> doubleMachineFigures;
    std::vector<std::shared_ptr<SingleMachineFigure>> singleMachineFigures;
    std::vector<std::shared_ptr<HalfMachineFigure>> halfMachineFigures;
    std::vector<std::shared_ptr<CarFigure>> _carFigures;

    std::shared_ptr<Queue<std::shared_ptr<Car>>> _cars;

    void initializeDoubleMachineFigures(const std::array<std::shared_ptr<DoubleMachine>, Config::linesCount>& machines);
    void initializeSingleMachineFigures();
    void initializeHalfMachineFigures();
    void initializeCarFigures();

    void refreshView();
    void refreshCarFigures();
};