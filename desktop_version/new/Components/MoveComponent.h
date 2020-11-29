#pragma once

#include "Component.h"
#include <math.h>

enum class EMove
{
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class MoveComponent : public Component
{
public:
    MoveComponent(SDL_Rect &pos)
        : Component()
        , pos(pos)
    {
    }
    void move(EMove m)
    {
        switch (m)
        {
        case EMove::RIGHT:
            pos.x++;
            break;
        case EMove::LEFT:
            pos.x--;
            break;
        case EMove::UP:
            pos.y++;
            break;
        case EMove::DOWN:
            pos.y--;
            break;
        }

        auto clip = [](auto x, auto _min, auto _max) -> auto
        {
            return std::min(_max, std::min(_max, 0));
        };
        pos.x = clip(pos.x, 0, 320 - pos.w);
        pos.y = clip(pos.y, 0, 240 - pos.h);
    }
    void update(void) override { return; }

protected:
    SDL_Rect &pos;
};