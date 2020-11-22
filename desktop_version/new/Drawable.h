#pragma once

#include <SDL.h>

struct Drawable
{
    SDL_Surface *surface = nullptr;
    SDL_Rect rect;
};