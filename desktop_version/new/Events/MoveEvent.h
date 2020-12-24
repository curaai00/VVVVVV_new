#pragma once

#include "../Components/GravityComponent.h"
#include "Event.h"
#include <math.h>
#include <tuple>

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
    MoveEvent(CollisionComponent *collision_checker, Drawable *pos)
        : Event()
        , pos(pos)
        , collision_checker(collision_checker)
    {
        key_buffer = std::make_pair(EMove::RIGHT, 0);
    }
    void update(SDL_Keycode k) override { move(convertMoveKey(k)); }

    void move(EMove m)
    {
        auto is_collisioned = collision_checker->is_collisioned();
        if (key_buffer.first == m)
        {
            key_buffer.second++;
        }
        else
        {
            key_buffer.first = m;
            key_buffer.second = 0;
        }

        if (4 <= key_buffer.second)
        {
            switch (m)
            {
            case EMove::RIGHT:
                if (is_collisioned & CollisionFlag::RIGHT) return;
                pos->rect.x += speed.x;
                break;
            case EMove::LEFT:
                if (is_collisioned & CollisionFlag::LEFT) return;
                pos->rect.x -= speed.x;
                break;
            case EMove::UP:
                pos->rect.y -= speed.y;
                break;
            case EMove::DOWN:
                pos->rect.y += speed.y;
                break;
            }

            auto clip = [](auto x, auto _min, auto _max) -> auto
            {
                return std::min(_max, std::min(_max, x));
            };
            pos->rect.x = clip(pos->rect.x, 0, 320 - pos->rect.w);
            pos->rect.y = clip(pos->rect.y, 0, 240 - pos->rect.h);
            key_buffer.second = 0;
        }
    }

protected:
    std::pair<EMove, int> key_buffer;
    Drawable *pos;
    CollisionComponent *collision_checker;
    SDL_Point speed{2, 3};
};