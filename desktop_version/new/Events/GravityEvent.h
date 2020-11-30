#pragma once

#include "../Components/GravityComponent.h"
#include "../Layer.h"
#include "Event.h"

class GravityEvent : public Event
{
public:
    GravityEvent(EGravityOrientation &ori)
        : Event()
        , ori(ori)
    {
    }

    void update(SDL_Keycode k)
    {
        if (k == SDLK_SPACE)
            ori = ori == EGravityOrientation::NATURELY
                      ? EGravityOrientation::REVERSED
                      : EGravityOrientation::NATURELY;
    }

protected:
    EGravityOrientation &ori;
};
