#pragma once

#include "SDL.h"
#include "util.h"

class Component
{
public:
    Component(SDL_Surface* _surface)
        : _surface(_surface){};

private:
    SDL_Surface* _surface;
};

class ColorComponent : public Component
{
public:
    ColorComponent(SDL_Surface* _surface, const SDL_Color& color)
        : Component(_surface)
        , _color(color)
    {}

    void set(const SDL_Color& c);
    SDL_Color color(void) { return _color; }

private:
    SDL_Color _color;
};
