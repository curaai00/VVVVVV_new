#pragma once

#include "../Components/GravityComponent.h"
#include "../Layer.h"
#include "Event.h"

class GravityEvent : public Event
{
public:
    GravityEvent(Drawable *drawable, CollisionComponent *collision_checker,
                 EGravityOrientation &ori)
        : Event()
        , collision_checker(collision_checker)
        , ori(ori)
        , _drawable(drawable)
    {
        // flip = new DynamicFlipComponent {}
    }

    void update(SDL_Keycode k)
    {
        if (k == SDLK_SPACE)
        {
            auto next = ori == EGravityOrientation::NATURELY
                            ? EGravityOrientation::REVERSED
                            : EGravityOrientation::NATURELY;
            auto is_collisioned = collision_checker->is_collisioned();
            if ((ori == EGravityOrientation::REVERSED &&
                 is_collisioned & CollisionFlag::UP) ||
                (ori == EGravityOrientation::NATURELY &&
                 is_collisioned & CollisionFlag::DOWN))
            {
                ori = next;
            }
        }
    }

protected:
    EGravityOrientation &ori;
    CollisionComponent *collision_checker;
    Drawable *_drawable;
    FlipComponent *flip;
};
