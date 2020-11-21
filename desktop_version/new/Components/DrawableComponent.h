#pragma once

#include "../Drawable.h"
#include "../Resource.h"
#include "../util.h"
#include "Component.h"

#include <iostream>
#include <utf8/unchecked.h>

class DrawableComponent : public virtual Component
{
public:
    DrawableComponent(const SDL_Rect &rect)
        : DrawableComponent(util::sdl::CreateSurface({rect.w, rect.h}), rect)
    {
    }

    DrawableComponent(SDL_Surface *surface, const SDL_Rect &rect)
        : Component()
        , _drawable({surface, rect})
    {
    }
    ~DrawableComponent(void) {}

    virtual void update(void) = 0;
    const Drawable &drawable(void) { return _drawable; }
    SDL_Surface *surface(void) { return _drawable.surface; }
    SDL_Rect rect(void) const { return _drawable.rect; }
    void set_rect(const SDL_Rect &rect) { _drawable.rect = rect; }

protected:
    Drawable _drawable;
};

class FullScreenComponent : public DrawableComponent
{
public:
    FullScreenComponent(void)
        : DrawableComponent({0, 0, 320, 240})
    {
    }

    virtual void update(void) = 0;
};

class StaticFullComponent : public FullScreenComponent
{
public:
    StaticFullComponent(void)
        : FullScreenComponent()
    {
    }
    ~StaticFullComponent(){};
    void update(void) { return; }
};

class AnimateComponent : public virtual DrawableComponent
{
public:
    AnimateComponent(const SDL_Rect &rect, unsigned int tick)
        : DrawableComponent(rect)
    {
    }
    AnimateComponent(SDL_Surface *surface, const SDL_Rect &rect, unsigned int tick)
        : DrawableComponent(surface, rect)
    {
    }

    virtual void update(void) = 0;

protected:
    unsigned int _tick = 0;
    unsigned int _duration = 0;
    bool _is_playing = false;
};

class MessageComponent : public DrawableComponent
{
public:
    MessageComponent(const TileAsset &font_tiles, const std::string &msg,
                     const SDL_Point &top_left, bool is_centred = false)
        : DrawableComponent(
              calc_rect(msg, is_centred ? cvt_center_pt(msg, top_left.y) : top_left))
    {
        SDL_Rect font_rect;

        int bfontpos = 0;
        auto iter = msg.cbegin();
        while (iter != msg.cend())
        {
            auto curr = utf8::unchecked::next(iter);
            font_rect = tfont_rect;
            font_rect.x = bfontpos;
            font_rect.y = 0;

            SDL_BlitSurface(font_tiles.tile(curr), NULL, surface(), &font_rect);
            bfontpos += curr < 32 ? 6 : 8;
        }
    }
    void update(void) override { return; }

protected:
    static SDL_Point cvt_center_pt(const std::string &msg, int y)
    {
        SDL_Point xy;

        xy.x = 160 - util::str::len(msg) / 2;
        xy.y = y;
        return xy;
    }
    static SDL_Rect calc_rect(const std::string &msg, const SDL_Point &top_left)
    {
        SDL_Rect rect;
        rect.x = top_left.x;
        rect.y = top_left.y;
        rect.w = util::str::len(msg);
        rect.h = tfont_rect.h;

        return rect;
    }
    static constexpr SDL_Rect tfont_rect{0, 0, 8, 8};
};