#pragma once

#include "../Eventable.h"

using InputComponent = Eventable;

class MoveComponent : public InputComponent
{
public:
    enum class Orientation : int
    {
        UP = 1,
        DOWN = -1
    };

    MoveComponent(SDL_Point &pos)
        : InputComponent()
        , _cur_pos(pos)
    {
        _speed = {1, 1};
        _orientation = Orientation::DOWN;
    }

    bool event(const SDL_Keycode k) override { throw NotImplementedError(); }

    SDL_Point speed(void) const { return _speed; }

protected:
    SDL_Point &_cur_pos;
    SDL_Point _speed;

    Orientation _orientation;
};