#pragma once

#include "Component.h "
#include <memory>

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

class ClearComponent : DrawingComponent
{
public:
    ColorComponent(SDL_Surface *surface)
        : DrawingComponent(surface)
    {
    }
    void update(void) override { SDL_FillRect(surface, NULL, 0); }
};

class ColorComponent : DrawingComponent
{
public:
    ColorComponent(SDL_Surface *surface, const SDL_Color &c)
        : DrawingComponent(surface)
    {
        set_color(c);
    }

    void update(void) override { return; }

    SDL_Color color(void) const { return _color; }
    void set_color(const SDL_Color &color)
    {
        _color = color;
        util::sdl::BlitSurfaceColoured(surface, _color);
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
        set_state(state);
    }

    void update(void) override { return; }

    void set_state(FlipState state)
    {
        using namespace util::sdl;

        const int w = _surface->w;
        const int h = _surface->h;

        auto flipped = CreateSurface({w, h});
        for (int x = 0, rx = w - 1; x < w; x++, rx--)
        {
            for (int y = 0, ry = h - 1; y < h; y++, ry--)
            {
                int dx = x;
                int dy = y;

                auto pixel = ReadPixel(_surface, x, y);
                if (_state.x) dx = rx;
                if (_state.y) dy = ry;
                DrawPixel(flipped, dx, dy, pixel);
            }
        }

        // copy surface directly for keep pointer reference
        auto pixel_size = h * _surface->pitch * _surface->format->BytesPerPixel;
        std::memcpy(_surface->pixels, flipped->pixels, pixel_size);

        SDL_FreeSurface(flipped);
    }

    FlipState state(void) const { return _state; }
    bool x_flipped(void) const { return _state.x; }
    bool y_flipped(void) const { return _state.y; }

protected:
    FlipState _state;
};
