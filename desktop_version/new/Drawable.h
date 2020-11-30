#pragma once

#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

struct Drawable
{
    SDL_Surface *surface = nullptr;
    SDL_Rect rect;

    Drawable &operator=(Drawable const &another);
};