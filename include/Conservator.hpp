#pragma once
#include "FactoryState.hpp"
#include "Machine.hpp"
#include "Random.hpp"
#include "SafeQueue.hpp"
#include "TextWindow.hpp"
#include <memory>
#include <thread>

class Conservator
{
public:
    Conservator(int x, int y,
      const std::string& name,
      const std::shared_ptr<const FactoryState>& factoryState,
      const std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>>& brokenMachines);
    ~Conservator();

    std::shared_ptr<TextWindow> figure() const;
    int x() const;
    int y() const;

private:
    std::atomic<int> _x;
    std::atomic<int> _y;
    const int _startX;
    const int _startY;

    std::shared_ptr<const FactoryState> _factoryState;
    std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>> _brokenMachines;
    std::shared_ptr<TextWindow> _figure;
    std::thread _thread;

    void work();
    void fixMachine(const std::shared_ptr<Machine>& machine);
};