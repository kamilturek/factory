#pragma once
#include "IWindow.hpp"
#include <algorithm>
#include <memory>
#include <vector>

class WindowSet : public IWindow
{
public:
    int x() const override;
    int y() const override;
    void redraw() override;
    void update() override;

protected:
    std::vector<std::unique_ptr<IWindow>> _windows;
};