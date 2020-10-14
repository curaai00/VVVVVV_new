#include "Sprite.h"

Sprite::Sprite(SDL_Point xy, std::string sprite_name)
    : Sprite(xy, Sprite::name2idx(sprite_name))
{
}

Sprite::Sprite(SDL_Point xy, unsigned int sprite_idx)
    : Drawable()
{
    auto size = sprite_tile.tilesize();
    _surface = util::sdl::CreateSurface({size.x, size.y});
    SDL_BlitSurface(sprite_tile.tile(sprite_idx), NULL, _surface,
                    NULL);

    _draw_rect.x = xy.x;
    _draw_rect.y = xy.y;
    _draw_rect.w = size.x;
    _draw_rect.h = size.y;
}

Sprite::~Sprite() {}

unsigned int Sprite::name2idx(std::string name)
{
    if (name == "V")
        return 23;
    else
        throw "Not implemented yet";
}

SpriteSet::SpriteSet(SDL_Point xy,
                     std::vector<unsigned int> sprite_idx_list)
    : Drawable()
{
    auto size = sprite_tile.tilesize();
    _surface = util::sdl::CreateSurface(
        {static_cast<int>(size.x * sprite_idx_list.size()), size.y});
    auto tile_size = sprite_tile.tilesize();
    SDL_Rect for_tile_rect{0, 0, tile_size.x, tile_size.y};

    for (int i = 0; i < sprite_idx_list.size(); i++)
    {
        SDL_BlitSurface(sprite_tile.tile(sprite_idx_list[i]), NULL,
                        _surface, &for_tile_rect);
        for_tile_rect.x += tile_size.x;
    }
    _draw_rect.x = xy.x;
    _draw_rect.y = xy.y;
    _draw_rect.w = tile_size.x * sprite_idx_list.size();
    _draw_rect.h = tile_size.y;
}
