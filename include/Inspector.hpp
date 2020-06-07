#pragma once
#include "FactoryState.hpp"
#include "Line.hpp"
#include "Machine.hpp"
#include "SafeQueue.hpp"
#include "TextWindow.hpp"
#include <memory>
#include <string>
#include <thread>

class Inspector
{
public:
    Inspector(int x, int y,
      const std::string& name,
      const Line& line,
      const std::shared_ptr<const FactoryState>& factoryState,
      const std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>>& brokenMachines);
    ~Inspector();

    std::shared_ptr<TextWindow> figure() const;
    int x() const;
    int y() const;

private:
    std::atomic<int> _x;
    std::atomic<int> _y;
    const int _startX;
    const int _startY;

    const Line& _line;

    std::shared_ptr<const FactoryState> _factoryState;
    std::shared_ptr<SafeQueue<std::shared_ptr<Machine>>> _brokenMachines;
    std::shared_ptr<TextWindow> _figure;

    std::thread _thread;

    void work();
};