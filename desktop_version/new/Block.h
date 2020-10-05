#pragma once

#include "Drawable.h"
#include "Resource.h"

class Block : public Drawable
{
public:
    Block(const std::array<unsigned short, SURFACE_ARR_SIZE>& room_arr,
          const TileAsset& tile_asset);
    ~Block();

    // TODO
    SDL_Point is_acrossed(SDL_Point point);
    bool is_transparent(void) const { return _is_transparent; }

    // TODO
    void construct(TileAsset& tile_asset);
    const std::vector<unsigned short>& block_indicies(void) { return _block_indicies; }
    const int tileCount(void);

protected:
    std::vector<unsigned short> _block_indicies;
    std::vector<SDL_Point> _block_tiles;
    bool _is_transparent = true;
};

class Wall : public Block
{
public:
    Wall(const std::array<unsigned short, SURFACE_ARR_SIZE>& room_arr,
         const TileAsset& tile_asset);
    ~Wall();
};

class Thorn : public Block
{
public:
    Thorn(const std::array<unsigned short, SURFACE_ARR_SIZE>& room_arr,
          const TileAsset& tile_asset);
    ~Thorn();
};

class BackWall : public Block
{
public:
    BackWall(const std::array<unsigned short, SURFACE_ARR_SIZE>& room_arr,
             const TileAsset& tile_asset);
    ~BackWall();
};
