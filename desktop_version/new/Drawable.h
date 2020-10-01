#pragma once

#include <SDL.h>

#ifndef SDL_BYTE_MASK
#define SDL_BYTE_MASK
const uint32_t R_MASK = 0x00ff0000;
const uint32_t G_MASK = 0x0000ff00;
const uint32_t B_MASK = 0x000000ff;
const uint32_t A_MASK = 0xff000000;
#endif

class Drawable
{
public:
    Drawable() {}
    virtual ~Drawable()
    {
        if (_surface)
            SDL_FreeSurface(_surface);
    }
    virtual void draw(void) = 0;
    SDL_Surface* getSurface(void) { return _surface; }
    SDL_Rect getDrawRect(void) { return _draw_rect; }

protected:
    SDL_Surface* _surface;
    SDL_Rect _draw_rect;
};

class ScreenDrawable : public Drawable
{
public:
    ScreenDrawable()
        : Drawable()
    {
        _surface = SDL_CreateRGBSurface(
            0, 320, 240, 32, R_MASK, G_MASK, B_MASK, A_MASK);
        _draw_rect = SDL_Rect{ 0, 0, 320, 240 };
    }
};

class ObjectDrawable : public Drawable
{
public:
    ObjectDrawable()
        : Drawable()
    {}
};