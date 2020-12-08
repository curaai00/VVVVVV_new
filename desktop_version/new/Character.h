#pragma once

#include "Components/DrawableComponent.h"
#include "Components/GravityComponent.h"
#include "Entity.h"
#include "Events/MoveEvent.h"

class Character : public DrawableEntity, public EventEntity
{
public:
    Character(const SDL_Point &tl)
        : DrawableEntity()
        , EventEntity()
    {
        auto tile = TileAsset{"graphics/sprites.png", {32, 32}};
        auto sprite = tile.tile(0);
        auto tight_rect = util::sdl::getTightRect(sprite);

        _drawable.surface = util::sdl::patch(sprite, tight_rect);
        _drawable.rect = {tl.x, tl.y, tight_rect.w, tight_rect.h};
    }

    void set_move_event(CollisionComponent* comp)
    {
        move_evt = new MoveEvent{comp, _drawable.rect};
        EventEntity::push(move_evt);
    };

    friend class Game;
    friend class Room;

protected:
    MoveEvent *move_evt = nullptr;
};