#include "UI.hpp"
#include "Factory.hpp"
#include <array>

void run()
{
    std::array<DoubleMachine, Config::linesCount> doubleMachines;

    UI ui;
    ui.initializeDoubleMachineFigures(doubleMachines);

    getch();   
}

int main(int /*argc*/, char const** /*argv*/)
{
    run();

    return 0;
}
