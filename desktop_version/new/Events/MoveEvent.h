#pragma once

#include "Event.h"
#include <math.h>

enum class EMove : SDL_Keycode
{
    RIGHT = SDLK_RIGHT,
    LEFT = SDLK_LEFT,
    UP = SDLK_UP,
    DOWN = SDLK_DOWN
};

inline EMove convertMoveKey(SDL_Keycode k)
{
    SDL_Keycode res;
    switch (k)
    {
    case SDLK_d:
        res = SDLK_RIGHT;
        break;
    case SDLK_a:
        res = SDLK_LEFT;
        break;
    case SDLK_w:
        res = SDLK_UP;
        break;
    case SDLK_s:
        res = SDLK_DOWN;
        break;
    default:
        // throw std::invalid_argument("Cannot convert to move key");
        break;
    }

    return static_cast<EMove>(res);
}

class MoveEvent : public Event
{
public:
    MoveEvent(SDL_Rect &pos)
        : Event()
        , pos(pos)
    {
    }
    void update(SDL_Keycode k) override { move(convertMoveKey(k)); }

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
            pos.y--;
            break;
        case EMove::DOWN:
            pos.y++;
            break;
        }

        auto clip = [](auto x, auto _min, auto _max) -> auto
        {
            return std::min(_max, std::min(_max, x));
        };
        pos.x = clip(pos.x, 0, 320 - pos.w);
        pos.y = clip(pos.y, 0, 240 - pos.h);
    }

protected:
    SDL_Rect &pos;
};