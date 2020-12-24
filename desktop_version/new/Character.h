#pragma once

#include "Components/Drawable/AnimatableComponent.h"
#include "Components/DrawableComponent.h"
#include "Components/GravityComponent.h"
#include "Entity.h"
#include "Events/GravityEvent.h"
#include "Events/MoveEvent.h"
#include "KeyPull.h"

class Character : public AnimatableEntity, public EventEntity
{
public:
    // Get current drawable for update then delete after update
    Character(const SDL_Point &tl)
        : AnimatableEntity()
        , EventEntity()
        , tl(tl)
    {
    }

    void generate_collision_component(SDL_Surface *room_surface)
    {
        AnimatableEntity::push(new MoveAnimationComponent{_drawable, tl, gravity});

        collide_comp = new CollisionComponent(room_surface, _drawable);
        AnimatableEntity::push(collide_comp);

        gravity_evt = new GravityEvent{_drawable, collide_comp, gravity};
        EventEntity::push(gravity_evt);
        move_evt = new MoveEvent{collide_comp, _drawable};
        EventEntity::push(move_evt);

        gravity_comp = new GravityComponent{_drawable, collide_comp, gravity};
        AnimatableEntity::push(gravity_comp);
    };

    friend class Game;
    friend class Room;

protected:
    SDL_Point tl;

    CollisionComponent *collide_comp = nullptr;
    MoveEvent *move_evt = nullptr;

    EGravityOrientation gravity = EGravityOrientation::NATURELY;
    GravityEvent *gravity_evt = nullptr;
    GravityComponent *gravity_comp = nullptr;
};