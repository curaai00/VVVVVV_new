#pragma once

#include "DrawingComponent.h"

class DynamicDrawingComponent : public Component
{
public:
    DynamicDrawingComponent(Drawable *drawable)
        : Component()
        , _drawable(drawable)
    {
    }
    SDL_Surface *surface(void) { return _drawable->surface; }
    virtual void update(void) = 0;

protected:
    Drawable *_drawable = nullptr;
};

class DynamicDrawToComponent : public DynamicDrawingComponent
{
public:
    DynamicDrawToComponent(Drawable *src, SDL_Surface *dst)
        : DynamicDrawingComponent(src)
        , dst(dst)
    {
    }
    void update(void) override
    {
        auto rect = _drawable->rect;
        SDL_BlitSurface(_drawable->surface, NULL, dst, &rect);
    }

protected:
    SDL_Surface *dst;
};

class DynamicFlipComponent : public DynamicDrawingComponent
{
public:
    struct FlipState
    {
        bool x;
        bool y;
    };

    DynamicFlipComponent(Drawable *drawable, FlipState state)
        : DynamicDrawingComponent(drawable)
    {
    }

    void update(void) override
    {
        using namespace util::sdl;

        auto cur_surface = surface();
        const int w = cur_surface->w;
        const int h = cur_surface->h;

        auto flipped = create({w, h});
        for (int x = 0, rx = w - 1; x < w; x++, rx--)
        {
            for (int y = 0, ry = h - 1; y < h; y++, ry--)
            {
                int dx = x;
                int dy = y;

                auto pixel = getPixel(cur_surface, x, y);
                if (_state.x) dx = rx;
                if (_state.y) dy = ry;
                setPixel(flipped, dx, dy, pixel);
            }
        }

        // copy surface directly for keep pointer reference
        util::sdl::copyTo(flipped, cur_surface);
        SDL_FreeSurface(flipped);
    }

    FlipState state(void) const { return _state; }
    bool x_flipped(void) const { return _state.x; }
    bool y_flipped(void) const { return _state.y; }

protected:
    FlipState _state;
};