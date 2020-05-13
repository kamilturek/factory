#pragma once

class IWindow
{
public:
    virtual int x() const = 0;
    virtual int y() const = 0;
    virtual void redraw() = 0;
    virtual void update() = 0;
    virtual ~IWindow(){};
};