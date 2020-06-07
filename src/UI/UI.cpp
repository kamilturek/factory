#include "UI.hpp"
#include <iostream>

UI::UI(std::shared_ptr<Factory> factory, const int refreshInterval) :
    _refreshInterval(refreshInterval), _factory(std::move(factory))
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();
    start_color();

    initializeMainWindow();
    initializeHelpWindow();
    initializeConservatorsWindow();
    initializeColors();

    initializeDoubleMachineFigures();
    initializeSingleMachineFigures();
    initializeHalfMachineFigures();

    _viewThread = std::make_unique<std::thread>(&UI::refreshView, this);
    _keyboardThread = std::make_unique<std::thread>(&UI::watchKeyboard, this);
}

UI::~UI()
{
    _keyboardThread->join();
    _viewThread->join();
}

void UI::watchKeyboard()
{
    while (_factory->state()->isWorking)
    {
        int keyPressed = wgetch(stdscr);

        switch (keyPressed)
        {
        // ESCAPE KEY
        case 27:
            _factory->stop();
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
    _mainWindow->printAt(3, 7, "AWAITING CARS: ");
    _mainWindow->printAt(3, 19, "AWAITING CARS: ");
    _mainWindow->printAt(3, 31, "AWAITING CARS: ");
    _mainWindow->printAt(3, 43, "AWAITING CARS: ");
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
    _helpWindow->printAt(30, 2, "COMPLETED: ");
    _helpWindow->printAt(30, 3, "IN PROGRESS: ");
}

void UI::initializeConservatorsWindow()
{
    constexpr int width = 48;
    constexpr int height = 5;
    constexpr int x = 187;
    constexpr int y = 46;

    _conservatorsWindow = std::make_unique<Window>(width, height, x, y);
    _conservatorsWindow->printAt(5, 0 ,"CONSERVATORS");
}

void UI::initializeColors()
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

void UI::initializeDoubleMachineFigures()
{
    for (int i = 0; i < 4; i++)
    {
        constexpr int offset = 1;
        constexpr int spacing = 12;
        constexpr int x = 20;
        const int y = offset + i * spacing;

        const auto machine = _factory->getLines().at(i).first;
        machine->x = x;
        machine->y = y;
        doubleMachineFigures.push_back(std::make_shared<DoubleMachineFigure>(x, y, i + 1));
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

        const auto machine = _factory->getLines().at(i).second;
        machine->x = x;
        machine->y = y;
        singleMachineFigures.push_back(std::make_unique<SingleMachineFigure>(x, y, i + 1));
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

        std::shared_ptr<Machine> machine;
        if (i == Config::linesCount)
        {
            hasStandBelow = false;
            machine = _factory->getLines().at(i - 1).thirdTwo;
        }
        else
            machine = _factory->getLines().at(i).thirdOne;

        machine->x = x;
        machine->y = y;
        halfMachineFigures.push_back(std::make_shared<HalfMachineFigure>(x, y, hasStandBelow, i + 1));
    }
}

void UI::refreshView()
{
    while (_factory->state()->isWorking)
    {
        refreshMachines();
        refreshCars();
        refreshConservators();
        refreshHelpWindow();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(_refreshInterval));
    }
}

void UI::refreshMachines()
{
    for (std::size_t i = 0; i < doubleMachineFigures.size(); i++)
    {
        const auto& machine = _factory->getLines().at(i).first;
        const auto& figure = doubleMachineFigures.at(i);
        figure->setUpperStandTaken(false);
        figure->redraw();
        mvprintw(figure->y() + 5, figure->x() + 15, std::to_string(machine->condition).c_str());
        printw("%%");
    }

    for (std::size_t i = 0; i < singleMachineFigures.size(); i++)
    {
        const auto& machine = _factory->getLines().at(i).second;
        const auto& figure = singleMachineFigures.at(i);
        figure->redraw();
        mvprintw(figure->y() + 1, figure->x() + 15, std::to_string(machine->condition).c_str());
        printw("%%");
    }

    for (std::size_t i = 0; i < halfMachineFigures.size(); i++)
    {
        std::shared_ptr<HalfMachine> machine;
        std::shared_ptr<HalfMachineFigure> figure;

        if (i == halfMachineFigures.size() - 1)
            machine = _factory->getLines().at(i - 1).thirdTwo;
        else
            machine = _factory->getLines().at(i).thirdOne;

        figure = halfMachineFigures.at(i);

        figure->redraw();
        mvprintw(figure->y() + 1, figure->x() + 15, std::to_string(machine->condition).c_str());
        printw("%%");
    }
}

void UI::refreshCars()
{
    std::array<int, Config::linesCount> awaitingCarsPerLine;
    awaitingCarsPerLine.fill(0);

    std::lock_guard<std::mutex> lock(_factory->cars()->mutex);

    for (const auto car : *_factory->cars())
    {
        const auto figure = car->figure();

        if (car->state() == State::WAITING)
        {
            awaitingCarsPerLine.at(car->line())++;
        }
        else if (car->state() == State::PHASE_ONE)
        {
            const auto machine = doubleMachineFigures.at(car->line());
            if (!machine->isUpperStandTaken())
            {
                figure->moveTo(machine->x() + 3, machine->y() + 1);
                machine->setUpperStandTaken(true);
            }
            else
                figure->moveTo(machine->x() + 3, machine->y() + 6);
        }
        else if (car->state() == State::PHASE_TWO)
        {
            const auto& machine = singleMachineFigures.at(car->line());
            figure->moveTo(machine->x() + 3, machine->y() + 2);
        }
        else if (car->state() == State::PHASE_THREE)
        {
            const auto machine = halfMachineFigures.at(car->line());
            figure->moveTo(machine->x() + 3, machine->y() + 2);
        }
        else if (car->state() == State::FINISHED)
        {
            figure->hide();
        }
        
        if (car->state() != State::WAITING && car->state() != State::FINISHED)
        {
            const int progress = static_cast<int>(car->progress() * 13);
            
            wattron(car->figure()->raw(), A_REVERSE);
            wattron(car->figure()->raw(), car->figure()->color());
            for (int i = 1; i < progress + 1; i++)
            {
                mvwprintw(car->figure()->raw(), 1, i, " ");
                mvwprintw(car->figure()->raw(), 2, i, " ");
            }
            wattroff(car->figure()->raw(), car->figure()->color());
            wattroff(car->figure()->raw(), A_REVERSE);
            wrefresh(car->figure()->raw());
        }
    }

    for (std::size_t i = 0; i < awaitingCarsPerLine.size(); i++)
    {
        constexpr int offset = 7;
        constexpr int spacing = 12;
        constexpr int x = 18;
        const int y = offset + static_cast<int>(i) * spacing;
        
        _mainWindow->printAt(x, y, "  ");
        _mainWindow->printAt(x, y, std::to_string(awaitingCarsPerLine.at(i)));
    }
}

void UI::refreshConservators()
{
    for (const auto& conservator : _factory->conservators())
    {
        if (conservator->figure()->x() != conservator->x() && conservator->figure()->y() != conservator->y())
        {
            conservator->figure()->moveTo(conservator->x(), conservator->y());
        }
        conservator->figure()->redraw();
    }
}

void UI::refreshHelpWindow()
{
    std::size_t carsCount;

    {
        std::lock_guard<std::mutex> lock(_factory->cars()->mutex);
        carsCount = _factory->cars()->size();
    }

    _helpWindow->printAt(46, 2, "   ");
    _helpWindow->printAt(51, 3, "   ");
    _helpWindow->printAt(41, 2, std::to_string(_factory->completedCars()));
    _helpWindow->printAt(43, 3, std::to_string(carsCount));
    _helpWindow->printAt(70, 2, "NEXT CAR SCHEDULE: " + std::to_string(_factory->nextSchedule()) + "\tms   ");
}