#include "Car.hpp"
#include "Factory.hpp"
#include "UI.hpp"

void run()
{
    auto factory = std::make_shared<Factory>();
    UI ui(factory);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    factory->setWorking(true);
    while (factory->isWorking());
}

int main(int /*argc*/, char const** /*argv*/)
{
    run();

    return 0;
}
