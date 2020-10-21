#pragma once

#include "../util.h"
#include "Component.h"

class DrawableComponent : public virtual Component
{
public:
    DrawableComponent(const SDL_Rect &rect)
        : DrawableComponent(util::sdl::CreateSurface({rect.w, rect.h}), rect)
    {
    }

    DrawableComponent(SDL_Surface *surface, const SDL_Rect &rect)
        : Component()
        , _surface(surface)
        , _rect(rect)
    {
    }

    virtual void update(void) = 0;
    SDL_Surface *surface(void) { return _surface; }
    SDL_Rect rect(void) const { return _rect; }

protected:
    SDL_Surface *_surface;
    SDL_Rect _rect;
};

class FullScreenComponent : public virtual DrawableComponent
{
public:
    FullScreenComponent(void)
        : DrawableComponent({0, 0, 320, 240})
    {
    }

    virtual void update(void) = 0;
};

class AnimateComponent : public virtual DrawableComponent
{
public:
    AnimateComponent(const SDL_Rect &rect, unsigned int tick)
        : DrawableComponent(rect)
    {
    }
    AnimateComponent(SDL_Surface *surface, const SDL_Rect &rect, unsigned int tick)
        : DrawableComponent(surface, rect)
    {
    }

    virtual void update(void) = 0;

protected:
    unsigned int _tick = 0;
    unsigned int _duration = 0;
    bool _is_playing = false;
};