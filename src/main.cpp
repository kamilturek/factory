#include "UI.hpp"
#include "Factory.hpp"
#include <array>

void run()
{
    Factory factory;
    UI ui(factory.getLines());

    getch();   
}

int main(int /*argc*/, char const** /*argv*/)
{
    run();

    return 0;
}
