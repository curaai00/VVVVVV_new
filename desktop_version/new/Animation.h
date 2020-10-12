#pragma once

#include "Component.h"
#include "Resource.h"

#include <vector>

class AnimateComponent : public Component
{
public:
    AnimateComponent(SDL_Surface *_surface, const SDL_Rect &_rect, unsigned int tick)
        : Component(_surface, _rect, Type::DYNAMIC), _duration(tick)
    {
    }

    virtual void update(void) = 0;
    bool is_playing(void) const
    {
        return _is_playing;
    }

private:
    unsigned int _animation_tick = 0;
    unsigned int _duration = 0;
    bool _is_playing;
};

class SpaceComponent : public AnimateComponent
{
public:
    SpaceComponent(void) : AnimateComponent(util::sdl::CreateSurface({320, 240}), SDL_Rect{320, 240}, 0)
    {
    }

    void update(void) override;

    struct Star
    {
        Star()
        {
            draw_rect = {Sint16(util::math::fRandom() * 320), Sint16(util::math::fRandom() * 240), 2, 2};
            speed = 4 + static_cast<int>(util::math::fRandom() * 4);
        }
        SDL_Rect draw_rect;
        int speed;
    };

private:
    static constexpr unsigned int num_stars = 50;
    Star stars[num_stars];
};

class StripeComponent : public AnimateComponent
{
public:
    StripeComponent(void) : AnimateComponent(util::sdl::CreateSurface({320, 240}), SDL_Rect{320, 240}, 0)
    {
        JsonAsset towerdata{"tower.json"};
        auto res = towerdata.asset.count("background");
        tower = towerdata.asset["background"].get<std::vector<unsigned short>>();
    }
    void update(void) override;

    unsigned int getColor(void) const
    {
        return _color;
    }
    void setColor(void);
    void setColor(unsigned int c);

private:
    TileAsset colortile{"graphics/tiles3.png", SDL_Point{8, 8}};

    std::vector<unsigned short> tower;

    unsigned int _color = 0;
    unsigned int _prev_color = 0;
    unsigned int _scroll_start_y = 0;
};
