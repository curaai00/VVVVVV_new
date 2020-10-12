#include "Animation.h"

void SpaceComponent::update(void)
{
    SDL_FillRect(_surface, NULL, 0);

    auto draw_star = [](SDL_Surface *surface, const SpaceComponent::Star &star) {
        Uint8 c = star.speed <= 6 ? 0x22 : 0x55;
        Uint32 color = SDL_MapRGB(surface->format, c, c, c);
        SDL_FillRect(surface, &star.draw_rect, color);
    };
    auto update_star = [](SpaceComponent::Star &star) {
        star.draw_rect.x -= star.speed;
        if (star.draw_rect.x < -10)
        {
            star.draw_rect.x += 340;
            star.draw_rect.y = int(util::math::fRandom() * 240);
            star.speed = 4 + int(util::math::fRandom() * 4);
        }
    };

    for (int i = 0; i < num_stars; i++)
    {
        update_star(stars[i]);
        draw_star(_surface, stars[i]);
    }
}

void StripeComponent::update(void)
{
    _scroll_start_y = (_scroll_start_y + 1) % 120;

    auto fill_tile = [&](int x, int y) {
        auto yoff = (_scroll_start_y + y) % 120;
        auto var = tower[yoff * 40 + x];
        SDL_Rect rect{x * 8, y * 8, 8, 8};
        SDL_BlitSurface(colortile.tile(var + _color * 30), NULL, _surface, &rect);
    };
    auto fill_row = [&](const int y) {
        for (int x = 0; x < 40; x++)
            fill_tile(x, y);
    };

    // optimization
    if (_prev_color == _color)
    {
        SDL_Rect prev_region{0, 8, 320, 240};
        SDL_Rect new_region{0, 0, 320, 232};
        SDL_BlitSurface(_surface, &prev_region, _surface, &new_region);
        fill_row(29);
    }
    else
    {
        for (int y = 0; y < 30; y++)
            fill_row(y);
    }
    _prev_color = _color;
}

void StripeComponent::setColor(void)
{
    _color = (_color + 1) % 30;
}

void StripeComponent::setColor(unsigned int c)
{
    if (0 <= c && c < 30)
        _color = c;
    else
        throw std::out_of_range("This Color out of tile colorspace");
}