#pragma once

#include "util.h"

class Drawable
{
public:
    Drawable() {}
    virtual ~Drawable() {}

    void draw_to_parent(SDL_Surface *parent)
    {
        SDL_BlitSurface(surface(), NULL, parent, &_draw_rect);
    }

    SDL_Surface *surface(void) { return _surface; }
    SDL_Rect rect(void) { return _draw_rect; }

protected:
    SDL_Surface *_surface;
    SDL_Rect _draw_rect;
};

class ScreenDrawable : virtual public Drawable
{
public:
    ScreenDrawable()
        : Drawable()
    {
        _surface = util::sdl::CreateSurface({320, 240});
        _draw_rect = SDL_Rect{0, 0, 320, 240};
    }
};
