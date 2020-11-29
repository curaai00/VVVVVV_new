#pragma once

#include "Components/DrawableComponent.h"
#include "Components/MoveComponent.h"
#include "Entity.h"

class Character : public DrawableEntity
{
public:
    Character(const SDL_Point &tl)
        : DrawableEntity()
    {
        auto tile = TileAsset{"graphics/sprites.png", {32, 32}};
        auto sprite = tile.tile(0);
        SDL_SaveBMP(sprite, "temp.png");
        auto tight_rect = util::sdl::getTightRect(sprite);

        _drawable.surface = util::sdl::patch(sprite, &tight_rect);
        _drawable.rect = {tl.x, tl.y, tight_rect.w, tight_rect.h};
        push(new MoveComponent{_drawable.rect});
    }

protected:
    MoveComponent *move_cpnt;
};