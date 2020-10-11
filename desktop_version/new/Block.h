#pragma once

#include "Drawable.h"
#include "Resource.h"

class Block : public Drawable
{
public:
    Block(const std::array<unsigned short, SURFACE_ARR_SIZE>& room_arr,
          const TileAsset& tile_asset) : Drawable(Type::STATIC){};
    ~Block(){};

    void update(void) override {return;}
    // TODO
    bool is_acrossed(const SDL_Point& point) const;
    bool is_transparent(void) const { return _is_transparent; }

    void construct(const std::array<unsigned short, SURFACE_ARR_SIZE>& room_arr,
                   const TileAsset& tile_asset);
    const std::vector<unsigned short>& block_indicies(void) { return _block_indicies; }
    // use this instaed of drawrect
    int tileCount(void) const { return static_cast<int>(_block_tiles.size()); }

protected:
    std::vector<unsigned short> _block_indicies;
    std::vector<SDL_Point> _block_tiles;
    bool _is_transparent = true;
};

class Wall : public Block
{
public:
    Wall(const std::array<unsigned short, SURFACE_ARR_SIZE>& room_arr,
         const TileAsset& tile_asset)
        : Block(room_arr, tile_asset)
    {
        _block_indicies = { 83, 124, 125, 163, 164, 165, 203, 205, 244 };
        construct(room_arr, tile_asset);
    }
    ~Wall(){};
};

class Thorn : public Block
{
public:
    Thorn(const std::array<unsigned short, SURFACE_ARR_SIZE>& room_arr,
          const TileAsset& tile_asset)
        : Block(room_arr, tile_asset)
    {
        _block_indicies = { 6 };
        construct(room_arr, tile_asset);
    }
    ~Thorn(){};
};

class BackWall : public Block
{
public:
    BackWall(const std::array<unsigned short, SURFACE_ARR_SIZE>& room_arr,
             const TileAsset& tile_asset)
        : Block(room_arr, tile_asset)
    {
        _block_indicies = { 680 };
        construct(room_arr, tile_asset);
    }
    ~BackWall(){};
};
