#pragma once

#include <vector>

#include "../Drawable.h"
#include "../Resource.h"
#include "../Sprite.h"
#include "../util.h"

using GraphicComponent = Drawable;

class AnimateComponent : virtual public GraphicComponent
{
public:
    AnimateComponent(unsigned int tick)
        : GraphicComponent()
        , _duration(tick)
    {
    }

    virtual void update(void) = 0;
    bool is_playing(void) const { return _is_playing; }
    bool is_infinite(void) const { return _duration == 0; }

protected:
    unsigned int _animation_tick = 0;
    unsigned int _duration = 0;
    bool _is_playing;
};

class MotionComponent : public AnimateComponent
{
public:
    MotionComponent(const std::vector<Sprite> &motions, SDL_Point &pos)
        : AnimateComponent(0)
        , _motions(motions)
        , _cur_pos(pos)
    {
        set(0);
    }

    void update(void) override
    {
        if (util::sdl::cmpPos(_cur_pos, _prev_pos)) set((_idx + 1) % length());
    }

    void set(unsigned int idx)
    {
        if (length() - 1 < idx)
            throw std::invalid_argument("Set motion idx out of range in motions");

        _idx = idx;
        _surface = _motions[idx].surface();
        _draw_rect = _motions[idx].rect();
    }
    unsigned int length(void) const
    {
        return static_cast<unsigned int>(_motions.size());
    }

protected:
    SDL_Point &_cur_pos;
    SDL_Point _prev_pos;
    std::vector<Sprite> _motions;
    unsigned int _idx;
};

class SpaceComponent : public AnimateComponent, public ScreenDrawable
{
public:
    SpaceComponent(void)
        : AnimateComponent(0)
        , ScreenDrawable()
    {
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

class StripeComponent : virtual public AnimateComponent,
                        virtual public ScreenDrawable
{
public:
    StripeComponent(void)
        : AnimateComponent(0)
        , ScreenDrawable()
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
