#pragma once

#include "Component.h"

class HMoveComponent : public Component, public Eventable
{
public:
    enum class HMoveKey : SDL_Keycode
    {
        LEFT = SDLK_LEFT,
        RIGHT = SDLK_RIGHT
    };

    HMoveComponent(SDL_Surface *surface, SDL_Rect &rect)
        : Component(surface, rect, )
        , Eventable()
    {
        throw NotImplementedError();
    }

    bool event(const SDL_Keycode k) override
    {
        throw NotImplementedError();
    };
    void move(const HMoveKey &k) { throw NotImplementedError(); };

    int speed(void) const { return _speed; }
    void setSpeed(int speed) { this->_speed = speed; }

private:
    int _speed;
};

class HMotionMoveComponent : public HMoveComponent
{
    HMotionMoveComponent(SDL_Surface *surface, SDL_Rect &rect)
        : HMoveComponent(surface, rect)
    {
        throw NotImplementedError();
    }
};