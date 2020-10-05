#pragma once

#include "Drawable.h"
#include "Resource.h"

#include <string>

class Sprite : public ObjectDrawable
{
public:
    Sprite(SDL_Point xy, std::string sprite_name);
    Sprite(SDL_Point xy, unsigned int sprite_idx);
    virtual ~Sprite();
    void draw(void) override { return; };
    void update(void) override { return; };
    static unsigned int name2idx(std::string name);

private:
    TileAsset sprite_tile{ "graphics/sprites.png", SDL_Point{ 32, 32 } };
};

class SpriteSet : public ObjectDrawable
{
public:
    SpriteSet(SDL_Point xy, std::vector<unsigned int> sprite_idx_list);
    virtual ~SpriteSet(){};
    void draw(void) override { return; };
    void update(void) override { return; };

private:
    TileAsset sprite_tile{ "graphics/sprites.png", SDL_Point{ 32, 32 } };
};