#pragma once

#include "Block.h"
#include "Layer.h"
#include "Resource.h"

#include <array>
#include <string>

class Room : public Layer
{
public:
    Room(const JsonAsset& room_table, const TileAsset& tile_asset, SDL_Point room_pos);
    ~Room();

    void update(void) override;

    std::string name(void) const { return _name; }

    // TODO
    int blockCount(void) const { return static_cast<int>(_blocks.size()); };
    const std::vector<Block*>& blocks(void) { return _blocks; }

private:
    SDL_Point _room_pos;
    std::string _name;

    std::array<unsigned short, SURFACE_ARR_SIZE> _cell_arr;
    std::vector<Block*> _blocks;
};
