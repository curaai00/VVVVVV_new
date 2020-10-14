#pragma once

#include "../util.h"

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
        SDL_Surface *temp_surface =
            util::sdl::CreateSurface({rect.w, rect.h});
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