#pragma once

#include "Drawable.h"
#include "Eventable.h"

class Character : public EventCompsitor
{
public:
    Character();
    ~Character();

    void flip(void)
    {
        _orientation = -_orientation;
    }

    enum class Orientation : int
    {
        UP = 1,
        DOWN = -1
    };

private:
    int xspeed;
    Orientation _orientation;

    HMoveComponent *hmove_component;
};