#pragma once

#include <SDL.h>

struct Drawable
{
    ~Drawable()
    {
        if (surface) SDL_FreeSurface(surface);
        delete surface;
    }
    SDL_Surface *surface;
    SDL_Rect rect;
};