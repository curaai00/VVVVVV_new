#pragma once

#include "Drawable.h"
#include "Resource.h"

#include <string>

class Sprite : public Drawable
{
public:
    Sprite(SDL_Point xy, std::string sprite_name);
    Sprite(SDL_Point xy, unsigned int sprite_idx);
    virtual ~Sprite();

    // Sprite(const Sprite &sprite);
    // Sprite &operator=(Sprite const &sprite);

    static unsigned int name2idx(std::string name);

private:
    TileAsset sprite_tile{"graphics/sprites.png", SDL_Point{32, 32}};
};

class SpriteSet : public Drawable
{
public:
    SpriteSet(SDL_Point xy, std::vector<unsigned int> sprite_idx_list);
    virtual ~SpriteSet(){};

private:
    TileAsset sprite_tile{"graphics/sprites.png", SDL_Point{32, 32}};
};