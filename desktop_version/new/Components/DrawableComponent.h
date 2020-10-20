#pragma once

#include "../util.h"
#include "Component.h"

class DrawableComponent : public Component
{
public:
    DrawableComponent(const SDL_Rect &rect)
        : DrawableComponent(util::sdl::CreateSurface(rect))
    {
    }

    DrawableComponent(SDL_Surface *surface, const SDL_Rect &rect)
        : Component()
        , _surface(surface)
        , _rect(rect)
    {
    }

    virtual void udpate(void) = 0;
    SDL_Surface *surface(void) { return _surface; }
    SDL_Rect rect(void) const { return _rect; }

protected:
    SDL_Surface *_surface;
    SDL_Rect _rect;
};

class FullScreenComponent : virtual public DrawableComponent
{
public:
    FullScreenComponent(void)
        : DrawableComponent({0, 0, 320, 240})
    {
    }

    virtual void udpate(void) = 0;
};

class AnimateComponent : virtual public DrawableComponent
{
public:
    AnimateComponent(SDL_Surface *surface, const SDL_Rect &rect, unsigned int tick)
        : DrawableComponent(surface, rect)
    {
        throw NotImplementedError();
    }

    virtual void udpate(void) = 0;

protected:
    unsigned int _tick = 0;
    unsigned int _duration = 0;
    bool _is_playing = false;
};
