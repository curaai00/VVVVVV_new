#pragma once

#include "../../KeyPull.h"
#include "../../Resource.h"
#include "../Component.h"
#include "../GravityComponent.h"

class AnimatableComponent : public Component
{
public:
    AnimatableComponent(const std::vector<SDL_Surface *> &animations)
        : Component()
        , animations(animations)
    {
        if (animations.size() == 0)
            throw std::invalid_argument("Zero sized animations");
    }
    virtual ~AnimatableComponent(){};

    SDL_Surface **surface(void) { return &animations[animate_idx]; }
    void set(int animate_idx)
    {
        if (animate_idx >= animations.size())
            std::out_of_range("Can't set that out of range in animations");

        this->animate_idx = animate_idx;
    }

    virtual void update(void) { return; }

protected:
    int animate_idx = 0;
    std::vector<SDL_Surface *> animations;
};

// TODO: make DrawAnimationComponent which parent of moveanimationcomponent
// that have update animation method, move animation have to have animation logic
class MoveAnimationComponent : public AnimatableComponent
{
public:
    MoveAnimationComponent(Drawable *target, const SDL_Point &pos,
                           const EGravityOrientation &gravity)
        : AnimatableComponent(get_ani_imgs())
        , target(target)
        , pos(pos)
        , gravity(gravity)
    {
        target->rect.x = pos.x;
        target->rect.y = pos.y;
    }
    ~MoveAnimationComponent()
    {
        for (auto animation : animations)
            delete animation;
    }

    void update(void)
    {
        update_counter--;

        animate_idx = 0;
        if (gravity == EGravityOrientation::REVERSED) animate_idx += 6;
        if (target->rect.x < prev.x) animate_idx += 3;

        // check pressed not only move check
        if (target->rect != prev)
        {
            // animation update logic
            if (update_counter <= 1)
            {
                update_counter = 4;
                internal_motion_idx++;
                if (internal_motion_idx >= 2) internal_motion_idx = 0;
                animate_idx = (animate_idx + internal_motion_idx + 1) %
                              (animations.size() - 1);
            }

            set(animate_idx);
            auto res = animations[animate_idx];
            auto tight_rect = util::sdl::getTightRect(res);
            target->surface = res;
            target->rect = {target->rect.x, target->rect.y, tight_rect.w,
                            tight_rect.h};
        }
        prev = target->rect;
    }

private:
    static const std::vector<SDL_Surface *> get_ani_imgs(void)
    {
        TileAsset sprites{"graphics/sprites.png", {32, 32}};
        std::vector<SDL_Surface *> res;
        for (int i = 0; i < 12; i++)
            res.push_back(util::sdl::copy(sprites.tile(i)));
        return res;
    }

protected:
    int update_counter = 4;
    int internal_motion_idx = 0;

    Drawable *target;
    SDL_Rect prev;
    const SDL_Point &pos;
    const EGravityOrientation &gravity;
};