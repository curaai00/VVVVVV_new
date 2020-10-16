#pragma once

#include "../util.h"
#include "InputComponent.h"

class DrawComponent
{
public:
    virtual void paint(SDL_Surface *to_draw) = 0;
};

class ColorComponent : public DrawComponent
{
public:
    ColorComponent(const SDL_Color &color)
        : DrawComponent()
        , _color(color)
    {
    }

    void paint(SDL_Surface *to_draw, const SDL_Rect &rect)
    {
        SDL_Surface *temp_surface = util::sdl::CreateSurface({rect.w, rect.h});
        SDL_BlitSurface(to_draw, &rect, temp_surface, NULL);

        paint(temp_surface);

        SDL_Rect temp_rect{rect};
        SDL_BlitSurface(temp_surface, NULL, to_draw, &temp_rect);
        SDL_FreeSurface(temp_surface);
    }
    virtual void paint(SDL_Surface *surface) override
    {
        using namespace util::sdl;
        const SDL_PixelFormat &fmt = *(surface->format);
        auto u_color = color2uint(surface, _color);

        for (int x = 0; x < surface->w; x++)
            for (int y = 0; y < surface->h; y++)
                if (ReadPixel(surface, x, y) & fmt.Amask)
                    DrawPixel(surface, x, y, u_color);
    }

    void set_color(const SDL_Color &c) { _color = c; }
    SDL_Color color(void) { return _color; }

private:
    SDL_Color _color;
};

// TODO: Implement Flip Draw Component
class FlipComponent : public DrawComponent
{
public:
    FlipComponent(bool x_flip, bool y_flip)
        : DrawComponent()
    {
    }

    void set_xflip(bool is_flipped) { x_flip = is_flipped; }
    void set_yflip(bool is_flipped) { y_flip = is_flipped; }

    void paint(SDL_Surface *to_draw) override
    {
        using namespace util::sdl;

        const int w = to_draw->w;
        const int h = to_draw->h;

        auto flipped = CreateSurface({w, h});
        for (int x = 0, rx = w - 1; x < w; x++, rx--)
        {
            for (int y = 0, ry = h - 1; y < h; y++, ry--)
            {
                int dx = x;
                int dy = y;

                auto pixel = ReadPixel(to_draw, x, y);
                if (x_flip) dx = rx;
                if (y_flip) dy = ry;
                DrawPixel(flipped, dx, dy, pixel);
            }
        }
    }

protected:
    bool x_flip;
    bool y_flip;
};