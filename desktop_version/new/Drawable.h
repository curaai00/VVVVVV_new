#pragma once

#include "util.h"

class Drawable
{
public:
    enum class Type
    {
        STATIC,
        DYNAMIC
    };

    Drawable(Type _type) : _type(_type)
    {
    }
    virtual ~Drawable()
    {
        SDL_FreeSurface(_surface);
    }

    virtual void update(void) = 0;
    SDL_Surface *surface(void)
    {
        return _surface;
    }
    SDL_Rect rect(void)
    {
        return _draw_rect;
    }
    Type type(void)
    {
        return _type;
    }

    void draw_to_parent(SDL_Surface *parent)
    {
        SDL_BlitSurface(surface(), NULL, parent, &_draw_rect);
    }

protected:
    SDL_Surface *_surface;
    SDL_Rect _draw_rect;
    const Type _type = Type::STATIC;
};

class ScreenDrawable : public Drawable
{
public:
    ScreenDrawable(Type _type) : Drawable(_type)
    {
        _surface = util::sdl::CreateSurface({320, 240});
        _draw_rect = SDL_Rect{0, 0, 320, 240};
    }
    virtual void update(void) = 0;
};
