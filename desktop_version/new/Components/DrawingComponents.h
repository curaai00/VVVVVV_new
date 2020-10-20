#pragma once

#include "Component.h "

#include "InputComponent.h"

class DrawingComponent
{
public:
    DrawingComponent(SDL_Surface *surface);

    SDL_Surface *surface(void) { return _surface; }
    virtual void update(void) = 0;

protected:
    SDL_Surface *_surface;
};

class ColorComponent : DrawingComponent
{
public:
    ColorComponent(SDL_Surface *surface, const SDL_Color &c)
        : DrawingComponent(surface)
    {
        throw NotImplementedError();
    }

    void update(void) override { return; }

    SDL_Color color(void) const { return _color; }
    void set_color(const SDL_Color &color)
    {
        _color = color;
        throw NotImplementedError();
    }

protected:
    SDL_Color _color;
};

class FlipComponent : public DrawingComponent
{
public:
    struct FlipState
    {
        bool x;
        bool y;
    };

    FlipComponent(SDL_Surface *surface, FlipState state)
        : DrawingComponent(surface)
    {
        throw NotImplementedError();
    }

    void update(void) override { return; }

    void set_state(FlipState state) { throw NotImplementedError(); }

    FlipState state(void) const { return _state; }
    bool x_flipped(void) const { return _state.x; }
    bool y_flipped(void) const { return _state.y; }

protected:
    FlipState _state;
};
