#pragma once
#include "Window.hpp"
#include "WindowSet.hpp"

class DoubleMachineFigure : public WindowSet
{
public:
    DoubleMachineFigure(int x, int y);

    bool isUpperStandTaken() const;
    void setUpperStandTaken(bool value);
    
private:
    bool _upperStandTaken;
};