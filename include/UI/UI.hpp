#pragma once
#include "Car.hpp"
#include "Config.hpp"
#include "DoubleMachine.hpp"
#include "DoubleMachineFigure.hpp"
#include "HalfMachineFigure.hpp"
#include "Line.hpp"
#include "SingleMachineFigure.hpp"
#include "Factory.hpp"
#include <array>
#include <memory>
#include <ncurses.h>
#include <vector>

class UI
{
public:
    UI(std::shared_ptr<Factory> factory);
    UI(const UI&) = delete;
    UI(UI&&) = delete;
    ~UI();

    UI& operator=(const UI&) = delete;
    UI& operator=(UI&&) = delete;

private:
    std::unique_ptr<std::thread> _viewThread;
    std::unique_ptr<std::thread> _keyboardThread;

    WINDOW* mainWindow;
    WINDOW* helpWindow;

    std::shared_ptr<Factory> _factory;

    std::vector<std::shared_ptr<DoubleMachineFigure>> doubleMachineFigures;
    std::vector<std::shared_ptr<SingleMachineFigure>> singleMachineFigures;
    std::vector<std::shared_ptr<HalfMachineFigure>> halfMachineFigures;

    void initializeDoubleMachineFigures();
    void initializeSingleMachineFigures();
    void initializeHalfMachineFigures();

    void initializeMainWindow();
    void initializeHelpWindow();

    void refreshView();
    void refreshMachines();
    void refreshCars();

    void watchKeyboard();
    void destroyWindow(WINDOW* window);
};