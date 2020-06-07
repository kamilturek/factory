#include "Car.hpp"
#include "Config.hpp"
#include "Factory.hpp"
#include "UI.hpp"
#include <getopt.h>
#include <iostream>

static int helpFlag = 0;
static int carsNumber = 3;
static int scheduleInterval = 5000;
static int collectInterval = 1000;
static int refreshInterval = 200;


void run()
{
    auto factory = std::make_shared<Factory>(carsNumber, scheduleInterval, collectInterval);
    UI ui(factory, refreshInterval);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    while (factory->isWorking());
}

int main(int argc, char** argv)
{
    int c;

    while (true)
    {
        static struct option longOptions[] = {
            { "help", no_argument, &helpFlag, 1 },
            { "ncars", required_argument, 0, 'n' },
            { "schedule-interval", required_argument, 0, 's' },
            { "collect-interval", required_argument, 0, 'c' },
            { "refresh-interval", required_argument, 0, 'r' },
            { 0, 0, 0, 0 }
        };

        int optionIndex;

        c = getopt_long(argc, argv, "n:s:c:r:", longOptions, &optionIndex);

        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            if (longOptions[optionIndex].flag != 0)
                break;
            break;
        case 'n':
            carsNumber = std::atoi(optarg);
            break;
        case 's':
            scheduleInterval = std::atoi(optarg);
            break;
        case 'c':
            collectInterval = std::atoi(optarg);
            break;
        case 'r':
            refreshInterval = std::atoi(optarg);
            break;
        default:
            return 0;
        }
    }

    if (helpFlag)
    {
        std::cout << "MULTITHREADED FACTORY | S02 PROJECT\n";
        std::cout << "KAMIL TUREK 2020\n\n";
        std::cout << "Optional arguments:\n";
        std::cout << "\t-n, --ncars=NUM\t\t\t\tnumber of cars to be scheduled each time\t\t(default: 3)\n";
        std::cout << "\t-s, --schedule-interval=NUM\t\ttime in milliseconds between new car scheduling\t\t(default: 5000)\n";
        std::cout << "\t-c, --collect-interval=NUM\t\ttime in milliseconds between completed cars collecting\t(default: 1000)\n";
        std::cout << "\t-r, --refresh-interval=NUM\t\ttime in milliseconds between view refreshing\t\t(default: 200)\n";
        return 0;
    }

    run();

    return 0;
}
