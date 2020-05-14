#pragma once
#include "Car.hpp"
#include "Config.hpp"
#include "DoubleMachine.hpp"
#include "DoubleMachineFigure.hpp"
#include "Factory.hpp"
#include "HalfMachineFigure.hpp"
#include "Line.hpp"
#include "SingleMachineFigure.hpp"
#include "Window.hpp"
#include <algorithm>
#include <array>
#include <memory>
#include <ncurses.h>
#include <vector>

class UI
{
public:
    UI(std::shared_ptr<Factory> factory, int refreshInterval);
    UI(const UI&) = delete;
    UI(UI&&) = delete;
    ~UI();

    UI& operator=(const UI&) = delete;
    UI& operator=(UI&&) = delete;

private:
    const int _refreshInterval;

    std::unique_ptr<std::thread> _viewThread;
    std::unique_ptr<std::thread> _keyboardThread;

    std::unique_ptr<Window> _mainWindow;
    std::unique_ptr<Window> _helpWindow;

    std::shared_ptr<Factory> _factory;

    std::vector<std::shared_ptr<DoubleMachineFigure>> doubleMachineFigures;
    std::vector<std::unique_ptr<SingleMachineFigure>> singleMachineFigures;
    std::vector<std::shared_ptr<HalfMachineFigure>> halfMachineFigures;

    void initializeDoubleMachineFigures();
    void initializeSingleMachineFigures();
    void initializeHalfMachineFigures();

    void initializeMainWindow();
    void initializeHelpWindow();
    void initializeColors();

    void refreshView();
    void refreshMachines();
    void refreshCars();
    void refreshHelpWindow();

    void watchKeyboard();
};