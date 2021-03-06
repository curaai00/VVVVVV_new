#pragma once

#include "../Drawable.h"
#include "../Resource.h"
#include "../util.h"
#include "../utils/sdl.h"
#include "../utils/str.h"
#include "Component.h"
#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <iostream>
#include <utf8/unchecked.h>

class DrawableComponent : public virtual Component
{
public:
    DrawableComponent(const SDL_Rect &rect)
        : DrawableComponent(util::sdl::create({rect.w, rect.h}), rect)
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
    MessageComponent(const SDL_Point &top_left, const std::string &msg,
                     bool is_centred = false)
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

            SDL_BlitSurface(font_asset.tile(curr), NULL, surface(), &font_rect);
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
    TileAsset font_asset{"graphics/font.png", SDL_Point{8, 8}};
};

class SpriteComponent : public DrawableComponent
{
public:
    SpriteComponent(
        const SDL_Point &tl, const std::vector<unsigned int> &sprite_idx,
        const std::vector<FlipStatus> &orientations = std::vector<FlipStatus>(),
        bool is_horizontal = true)
        : DrawableComponent(calc_rect(tl, sprite_idx.size(), is_horizontal))
        , _sprite_idx(sprite_idx)
        , _orientations(orientations)
    {
        // if use default
        if (orientations.size() != sprite_idx.size())
            _orientations = std::vector<FlipStatus>(sprite_idx.size(), FlipStatus());

        auto get_tile =
            [&tiles = sprite_tile](
                const unsigned int &idx,
                const util::sdl::FlipStatus &orientation) -> SDL_Surface * {
            auto tile = tiles.tile(idx);
            return util::sdl::rotate(tile, orientation);
        };

        std::vector<SDL_Surface *> tiles;
        for (auto i : util::range<int>(0, _sprite_idx.size()))
            tiles.push_back(get_tile(_sprite_idx[i], _orientations[i]));

        for (int i = 0; i < tiles.size(); i++)
        {
            SDL_Rect rect;
            if (is_horizontal)
                rect = SDL_Rect{i * tilesize, 0, tilesize, tilesize};
            else
                rect = SDL_Rect{0, i * tilesize, tilesize, tilesize};
            util::sdl::blit(tiles[i], NULL, surface(), &rect);
        }

        for (auto tile : tiles)
            util::sdl::destroy(tile);
    }
    ~SpriteComponent();
    void update(void) override { return; }

private:
    static SDL_Rect calc_rect(const SDL_Point &tl, int size, bool is_horizontal)
    {
        SDL_Point wh;
        wh = is_horizontal ? SDL_Point{tilesize * size, tilesize}
                           : SDL_Point{tilesize, tilesize * size};
        return SDL_Rect{tl.x, tl.y, wh.x, wh.y};
    }

private:
    std::vector<unsigned int> _sprite_idx;
    std::vector<FlipStatus> _orientations;

    static constexpr int tilesize = 32;
    TileAsset sprite_tile{"graphics/sprites.png", SDL_Point{tilesize, tilesize}};
};
