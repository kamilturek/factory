#include "UI.hpp"
#include "Figure.hpp"

UI::UI(std::shared_ptr<Factory> factory) :
    _factory(std::move(factory))
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();

    initializeMainWindow();
    initializeHelpWindow();

    initializeDoubleMachineFigures();
    initializeSingleMachineFigures();
    initializeHalfMachineFigures();

    _factory->createCar();
    _factory->createCar();
    _factory->createCar();
    _factory->createCar();
    _factory->createCar();
    _factory->createCar();

    _viewThread = std::make_unique<std::thread>(&UI::refreshView, this);
    _keyboardThread = std::make_unique<std::thread>(&UI::watchKeyboard, this);
}

UI::~UI()
{
    _keyboardThread->join();
    _viewThread->join();
    endwin();
}

void UI::watchKeyboard()
{
    while (_factory->isWorking())
    {
        int keyPressed = wgetch(stdscr);

        switch (keyPressed)
        {
        // ESCAPE KEY
        case 27:
            _factory->setWorking(false);
            break;
        }
    }
}

void UI::initializeMainWindow()
{
    constexpr int width = 237;
    constexpr int height = 52;
    constexpr int x = 0;
    constexpr int y = 0;

    _mainWindow = std::make_unique<Window>(width, height, x, y);

    const std::string leftHeader = "MULTITHREADED FACTORY | SO2";
    const std::string rightHeader = "KAMIL TUREK 2020";

    _mainWindow->printAt(5, 0, leftHeader);
    _mainWindow->printAt(237 - static_cast<int>(rightHeader.length()) - 5, 0, rightHeader);
}

void UI::initializeHelpWindow()
{
    constexpr int width = 237;
    constexpr int height = 5;
    constexpr int x = 0;
    constexpr int y = 52;

    _helpWindow = std::make_unique<Window>(width, height, x, y);
    _helpWindow->printAt(5, 0, "HELP");
    _helpWindow->printAt(1, 3, "[ESC] - EXIT PROGRAM");
}

void UI::initializeDoubleMachineFigures()
{
    for (int i = 0; i < 4; i++)
    {
        constexpr int offset = 1;
        constexpr int spacing = 12;
        constexpr int x = 20;
        const int y = offset + i * spacing;

        doubleMachineFigures.push_back(std::make_shared<DoubleMachineFigure>(x, y));
    }
}

void UI::initializeSingleMachineFigures()
{
    for (int i = 0; i < Config::linesCount; i++)
    {
        constexpr int offset = 3;
        constexpr int spacing = 12;
        constexpr int x = 110;
        const int y = offset + i * spacing;

        singleMachineFigures.push_back(std::make_unique<SingleMachineFigure>(x, y));
    }
}

void UI::initializeHalfMachineFigures()
{
    for (int i = 0; i < Config::linesCount + 1; i++)
    {
        constexpr int offset = 10;
        constexpr int spacing = 6;
        constexpr int x = 196;
        const int y = offset + i * spacing;
        bool hasStandBelow = true;

        if (i == Config::linesCount)
            hasStandBelow = false;

        halfMachineFigures.push_back(std::make_shared<HalfMachineFigure>(x, y, hasStandBelow));
    }
}

void UI::refreshView()
{
    while (_factory->isWorking())
    {
        refreshMachines();
        refreshCars();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void UI::refreshMachines()
{
    for (const auto& machine : doubleMachineFigures)
    {
        machine->setUpperStandTaken(false);
        machine->redraw();
    }

    for (const auto& machine : singleMachineFigures)
        machine->redraw();

    for (const auto& machine : halfMachineFigures)
        machine->redraw();
}

void UI::refreshCars()
{
    std::array<int, Config::linesCount> awaitingCarsPerLine;
    awaitingCarsPerLine.fill(0);

    for (const auto& car : _factory->getCars())
    {
        if (car->getState() == State::WAITING)
        {
            awaitingCarsPerLine.at(car->getLineNumber())++;
        }
        else if (car->getState() == State::PHASE_ONE)
        {
            const auto machine = doubleMachineFigures.at(car->getLineNumber());
            if (!machine->isUpperStandTaken())
            {
                car->_figure->moveTo(machine->y() + 1, machine->x() + 3);
                machine->setUpperStandTaken(true);
            }
            else
                car->_figure->moveTo(machine->y() + 6, machine->x() + 3);
            car->_figure->refresh();
        }
        else if (car->getState() == State::PHASE_TWO)
        {
            const auto& machine = singleMachineFigures.at(car->getLineNumber());
            car->_figure->moveTo(machine->y() + 2, machine->x() + 3);
            car->_figure->refresh();
        }
        else if (car->getState() == State::PHASE_THREE)
        {
            const auto machine = halfMachineFigures.at(car->getLineNumber());
            car->_figure->moveTo(machine->y() + 2, machine->x() + 3);
            car->_figure->refresh();
        }
        else if (car->getState() == State::FINISHED)
        {
            car->_figure->moveTo(-99, -99);
        }
    }

    // Print awaiting
    for (std::size_t i = 0; i < awaitingCarsPerLine.size(); i++)
    {
        constexpr int offset = 7;
        constexpr int spacing = 12;
        constexpr int colIndex = 3;
        const int rowIndex = offset + i * spacing;

        const std::string text = "Awaiting cars: " + std::to_string(awaitingCarsPerLine.at(i));

        mvwprintw(_mainWindow->raw(), rowIndex, colIndex, text.c_str());
    }

    _mainWindow->update();
}