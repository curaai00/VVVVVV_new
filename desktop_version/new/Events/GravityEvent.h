#pragma once

#include "../Components/GravityComponent.h"
#include "../Layer.h"
#include "Event.h"

class GravityEvent : public Event
{
public:
    GravityEvent(CollisionComponent *collision_checker,
                 EGravityOrientation ori = EGravityOrientation::NATURELY)
        : Event()
        , collision_checker(collision_checker)
        , ori(ori)
    {
    }

    void update(SDL_Keycode k)
    {
        if (k == SDLK_SPACE)
        {
            auto next = ori == EGravityOrientation::NATURELY
                            ? EGravityOrientation::REVERSED
                            : EGravityOrientation::NATURELY;
            auto is_collisioned = collision_checker->is_collisioned();
            if (ori == EGravityOrientation::REVERSED &&
                is_collisioned & CollisionFlag::UP)
                ori = next;
            else if (ori == EGravityOrientation::NATURELY &&
                     is_collisioned & CollisionFlag::DOWN)
                ori = next;
        }
    }

    const EGravityOrientation &get_orientation(void) { return ori; }

protected:
    EGravityOrientation ori;
    CollisionComponent *collision_checker;
};
