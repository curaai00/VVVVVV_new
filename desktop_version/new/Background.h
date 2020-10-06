#pragma once

#include "Layer.h"
#include "Resource.h"
#include "util.h"

#include <SDL.h>

#include <array>
#include <vector>

class IntroBackground : public ScreenDrawable
{
public:
    IntroBackground();
    virtual ~IntroBackground();

    void draw(void) override;
    void update(void) override;

private:
    void scroll(void);

public:
    JsonAsset towerdata{ "tower.json" };
    TileAsset colortile{ "graphics/tiles3.png", SDL_Point{ 8, 8 } };

    std::vector<unsigned short> tower;

    unsigned int getColor(void) const;
    void setColor(void);
    void setColor(unsigned int c);

private:
    unsigned int _color = 0;
    unsigned int _prev_color = -1; // use for optimization when draw
    unsigned int _scroll_start_y = 0;
};

class SpaceBackground : public ScreenDrawable
{
public:
    SpaceBackground();
    virtual ~SpaceBackground();

    void draw(void) override;
    void update(void) override;

    struct Star
    {
        Star()
        {
            draw_rect = { Sint16(util::math::fRandom() * 320),
                          Sint16(util::math::fRandom() * 240),
                          2,
                          2 };
            speed = 4 + static_cast<int>(util::math::fRandom() * 4);
        }
        SDL_Rect draw_rect;
        int speed;
    };

private:
    static constexpr unsigned int num_stars = 50;
    Star stars[num_stars];
};