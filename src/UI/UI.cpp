#include "UI.hpp"
#include "Figure.hpp"

UI::UI(const std::array<Line, Config::linesCount>& lines, std::shared_ptr<Queue<std::shared_ptr<Car>>> cars) :
    _viewThread(&UI::refreshView, this), _cars(cars)
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();

    initializeDoubleMachineFigures({
      lines.at(0).first,
      lines.at(1).first,
      lines.at(2).first,
      lines.at(3).first,
    });
}

UI::~UI()
{
    endwin();
}

void UI::initializeDoubleMachineFigures(const std::array<std::shared_ptr<DoubleMachine>, Config::linesCount>& machines)
{
    for (std::size_t i = 0; i < Config::linesCount; i++)
    {
        constexpr int offset = 1;
        constexpr int spacing = 14;
        constexpr int colIndex = 20;
        const int rowIndex = offset + static_cast<int>(i) * spacing;

        doubleMachineFigures.push_back(std::make_shared<DoubleMachineFigure>(rowIndex, colIndex, machines.at(i)));
    }
}

void UI::initializeSingleMachineFigures()
{
    for (int i = 0; i < Config::linesCount; i++)
    {
        constexpr int offset = 3;
        constexpr int spacing = 14;
        constexpr int colIndex = 110;
        const int rowIndex = offset + i * spacing;

        singleMachineFigures.push_back(std::make_shared<SingleMachineFigure>(rowIndex, colIndex));
    }
}

void UI::initializeHalfMachineFigures()
{
    for (int i = 0; i < Config::linesCount + 1; i++)
    {
        constexpr int offset = 14;
        constexpr int spacing = 6;
        constexpr int colIndex = 196;
        const int rowIndex = offset + i * spacing;
        bool hasStandBelow = true;

        if (i == Config::linesCount)
            hasStandBelow = false;

        halfMachineFigures.push_back(std::make_shared<HalfMachineFigure>(rowIndex, colIndex, hasStandBelow));
    }
}

void UI::initializeCarFigures()
{
    std::lock_guard<std::mutex> lock(_cars->mutex);
    while (!_cars->queue.empty())
    {
        _carFigures.push_back(std::make_shared<CarFigure>(_cars->queue.front()));
        _cars->queue.pop();
    }
}

void UI::refreshView()
{
    std::this_thread::sleep_for(Config::refreshInterval);
    initializeCarFigures();
    refreshCarFigures();
}

void UI::refreshCarFigures()
{
    std::array<int, Config::linesCount> awaitingCarsPerLine;
    awaitingCarsPerLine.fill(0);

    for (const auto& carFigure : _carFigures)
    {
        const auto car = carFigure->getCar();
        if (car->getState() == State::WAITING)
        {
            awaitingCarsPerLine.at(car->getLineNumber())++;
        }
    }

    for (std::size_t i = 0; i < awaitingCarsPerLine.size(); i++)
    {
        constexpr int rowOffset = -8;
        constexpr int colOffset = -18;
        const auto coords = Config::doubleMachinePositions.at(i);
        const auto text = "Awaiting cars: " + std::to_string(awaitingCarsPerLine.at(i));
        mvprintw(coords.first + rowOffset, coords.second + colOffset, text.c_str());
    }

    refresh();
}