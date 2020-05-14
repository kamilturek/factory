#pragma once
#include "Window.hpp"
#include "WindowSet.hpp"

class DoubleMachineFigure : public WindowSet
{
public:
    DoubleMachineFigure(int x, int y, int number);

    bool isUpperStandTaken() const;
    void setUpperStandTaken(bool value);

    void redraw() override;
    
private:
    bool _upperStandTaken;
    const int _number;
};