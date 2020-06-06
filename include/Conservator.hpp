#pragma once
#include "Machine.hpp"
#include "SafeQueue.hpp"
#include "TextWindow.hpp"
#include "Random.hpp"
#include <memory>
#include <thread>

class Conservator
{
public:
    Conservator(int x, int y,
                const std::string& name, const std::atomic<bool>& isFactoryWorking,
                const std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>>& brokenMachines);
    ~Conservator();

    std::shared_ptr<TextWindow> figure() const;

private:
    const int _x;
    const int _y;

    const std::atomic<bool>& _isFactoryWorking;
    std::thread _thread;
    std::shared_ptr<TextWindow> _figure;
    std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>> _brokenMachines;

    void work();
    void fixMachine(const std::shared_ptr<Machine>& machine);
};