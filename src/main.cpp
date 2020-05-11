#include "Car.hpp"
#include "Factory.hpp"
#include "UI.hpp"

void run()
{
    Factory factory;
    UI ui(factory.getLines(), factory.getCars());
    factory.createCar();
    factory.createCar();
    factory.createCar();

    getch();
}

int main(int /*argc*/, char const** /*argv*/)
{
    run();

    return 0;
}
