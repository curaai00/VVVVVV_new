#pragma once

#include "Drawable.h"
#include "util.h"

class Component : public Drawable
{
public:
    Component(SDL_Surface* surface, const SDL_Rect& rect, Type _type)
        : Drawable(_type)
    {
        this->_surface = surface;
        this->_draw_rect = rect;
    };
};

class ColorComponent : public Component
{
public:
    ColorComponent(SDL_Surface* surface, const SDL_Rect& rect, const SDL_Color& color)
        : Component(surface, rect, Type::STATIC)
        , _color(color)
    {}

    void set(const SDL_Color& c);
    SDL_Color color(void) { return _color; }

private:
    SDL_Color _color;
};
