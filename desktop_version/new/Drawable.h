#pragma once

#include <SDL.h>

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
            0, 320, 240, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
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