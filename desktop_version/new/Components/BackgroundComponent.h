#pragma once

#include "../Resource.h"
#include "../Sprite.h"
#include "DrawableComponent.h"

class BackgroundComponent : public AnimateComponent, public FullScreenComponent
{
public:
    BackgroundComponent(void)
        : AnimateComponent(NULL, {0, 0, 0, 0}, 0)
        , FullScreenComponent()
    {
    }
    virtual void udpate(void) = 0;
};

class SpaceComponent : public BackgroundComponent
{
public:
    SpaceComponent(void)
        : BackgroundComponent()
    {
        throw NotImplementedError();
    }
    void update(void) override;

    struct Star
    {
        Star()
        {
            draw_rect = {Sint16(util::math::fRandom() * 320),
                         Sint16(util::math::fRandom() * 240), 2, 2};
            speed = 4 + static_cast<int>(util::math::fRandom() * 4);
        }
        SDL_Rect draw_rect;
        int speed;
    };

private:
    static constexpr unsigned int num_stars = 50;
    Star stars[num_stars];
};

class StripeComponent : public BackgroundComponent
{
public:
    StripeComponent(void)
        : BackgroundComponent()
    {

        JsonAsset towerdata{"tower.json"};
        auto res = towerdata.asset.count("background");
        tower = towerdata.asset["background"].get<std::vector<unsigned short>>();
    }
    void update(void) override;

    unsigned int getColor(void) const { return _color; }
    void setColor(void);
    void setColor(unsigned int c);

private:
    TileAsset colortile{"graphics/tiles3.png", SDL_Point{8, 8}};

    std::vector<unsigned short> tower;

    unsigned int _color = 0;
    unsigned int _prev_color = 0;
    unsigned int _scroll_start_y = 0;
};
