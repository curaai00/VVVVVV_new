#include "Sprite.h"

Sprite::Sprite(SDL_Point xy, std::string sprite_name)
    : Sprite(xy, Sprite::name2idx(sprite_name))
{}

Sprite::Sprite(SDL_Point xy, unsigned int sprite_idx)
    : ObjectDrawable()
{
    auto size = sprite_tile.getTileSize();
    _surface = SDL_CreateRGBSurface(
        0, size.x, size.y, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    SDL_BlitSurface(sprite_tile.getTile(sprite_idx), NULL, _surface, NULL);

    _draw_rect.x = xy.x;
    _draw_rect.y = xy.y;
    _draw_rect.w = size.x;
    _draw_rect.h = size.y;
}

Sprite::~Sprite() {}

void Sprite::draw(void) {}

unsigned int Sprite::name2idx(std::string name)
{
    if (name == "V")
        return 23;
    else
        throw "Not implemented yet";
}