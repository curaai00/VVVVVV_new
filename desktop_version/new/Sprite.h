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
    void draw(void) override;
    static unsigned int name2idx(std::string name);

private:
    TileAsset sprite_tile{ "graphics/sprites.png", SDL_Point{ 32, 32 } };
};
