#pragma once

#include "../Resource.h"
#include "DrawableComponent.h"

class StripeComponent : public AnimateComponent
{
public:
    StripeComponent(void)
        : DrawableComponent({0, 0, 320, 240})
        , AnimateComponent({0, 0, 0, 0}, 0)
    {

        JsonAsset towerdata{"tower.json"};
        auto res = towerdata.asset.count("background");
        tower = towerdata.asset["background"].get<std::vector<unsigned short>>();
    }
    void update(void) override
    {
        _scroll_start_y = (_scroll_start_y + 1) % 120;

        auto fill_tile = [&](int x, int y) {
            auto yoff = (_scroll_start_y + y) % 120;
            auto var = tower[yoff * 40 + x];
            SDL_Rect rect{x * 8, y * 8, 8, 8};
            SDL_BlitSurface(colortile.tile(var + _color * 30), NULL, surface(),
                            &rect);
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
            SDL_BlitSurface(surface(), &prev_region, surface(), &new_region);
            fill_row(29);
        }
        else
        {
            for (int y = 0; y < 30; y++)
                fill_row(y);
        }
        _prev_color = _color;
    }

    unsigned int getColor(void) const { return _color; }
    void setColor(void);
    void setColor(unsigned int c);

private:
    TileAsset colortile{"graphics/tiles3.png", SDL_Point{8, 8}};

    std::vector<unsigned short> tower;

    unsigned int _color = 0;
    unsigned int _prev_color = 1;
    unsigned int _scroll_start_y = 0;
};
