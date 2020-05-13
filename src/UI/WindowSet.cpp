#include "WindowSet.hpp"

void WindowSet::redraw()
{
    for (const auto& window : _windows)
        window->redraw();
}

void WindowSet::update()
{
    for (const auto& window : _windows)
        window->update();
}

int WindowSet::x() const
{
    const auto& minXWindow = std::min_element(_windows.cbegin(), _windows.cend(), [](const auto& a, const auto& b) { return a->x() < b->x(); });
    return (*minXWindow)->x();
}

int WindowSet::y() const
{
    const auto& minYWindow = std::min_element(_windows.cbegin(), _windows.cend(), [](const auto& a, const auto& b) { return a->y() < b->y(); });
    return (*minYWindow)->y();
}