#pragma once

#include "Components/DrawComponents.h"
#include "Components/GraphicComponents.h"
#include "Components/InputComponent.h"
#include "Eventable.h"
#include "Sprite.h"

class Character : public EventCompsitor, public Drawable
{
public:
    Character(const SDL_Point &start_pos)
        : _pos(start_pos)
    {

        _motion = new MotionComponent{
            std::vector<Sprite>{Sprite{{0, 0}, 0}, Sprite{{0, 0}, 1}}, _pos};
        _move = new MoveComponent{_pos};

        addEventable(_move);

        _surface = _motion->surface();
        _draw_rect = _motion->rect();
        _draw_rect.x = _pos.x;
        _draw_rect.y = _pos.y;
    }
    ~Character()
    {
        delete _motion;
        delete _move;
    }

    void update(void)
    {
        _motion->update();

        _surface = _motion->surface();
        _draw_rect = _motion->rect();
        _draw_rect.x = _pos.x;
        _draw_rect.y = _pos.y;
    }

protected:
    Sprite char_sprite_normal{{0, 0}, 0};
    Sprite char_sprite_move{{0, 0}, 1};

    MoveComponent *_move;
    MotionComponent *_motion;
    FlipComponent _flip{false, false};

    SDL_Point _pos;
};