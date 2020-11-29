#pragma once

#include "../Drawable.h"
#include "../utils/sdl.h"
#include "Component.h"
#include <memory>

class DrawingComponent : public Component
{
public:
    DrawingComponent(SDL_Surface *surface)
        : Component()
        , _surface(surface){};

    SDL_Surface *surface(void) { return _surface; }
    virtual void update(void) = 0;

protected:
    SDL_Surface *_surface;
};

class DrawToComponent : public DrawingComponent
{
public:
    DrawToComponent(const Drawable &src, const Drawable &dst)
        : DrawingComponent(dst.surface)
        , src(src)
        , dst(dst)
    {
    }
    void update(void) override
    {
        SDL_BlitSurface(src.surface, NULL, dst.surface, &src.rect);
    }

protected:
    Drawable src;
    Drawable dst;
};

class ClearComponent : public DrawingComponent
{
public:
    ClearComponent(SDL_Surface *surface)
        : DrawingComponent(surface)
    {
    }
    void update(void) override { SDL_FillRect(_surface, NULL, 0); }
};

class ColorComponent : public DrawingComponent
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
        util::sdl::fillColor(_surface, _color);
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

        auto flipped = create({w, h});
        for (int x = 0, rx = w - 1; x < w; x++, rx--)
        {
            for (int y = 0, ry = h - 1; y < h; y++, ry--)
            {
                int dx = x;
                int dy = y;

                auto pixel = getPixel(_surface, x, y);
                if (_state.x) dx = rx;
                if (_state.y) dy = ry;
                setPixel(flipped, dx, dy, pixel);
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

class RotationComponent : public DrawingComponent
{
public:
    RotationComponent(SDL_Surface *surface, util::sdl::FlipStatus flip)
        : DrawingComponent(surface)
    {
        util::sdl::rotate(surface, flip);
    }

    ~RotationComponent() {}

    void update(void) override { return; }

private:
    util::sdl::FlipStatus flip_status;
};
