#pragma once

#include "Block.h"
#include "Drawable.h"
#include "Resource.h"
#include <array>
#include <string>

class Map : public ScreenDrawable
{
public:
    // TODO  map has resources, when move room give resourse with construct
    Map(int roomx, int roomy);
    virtual ~Map();

    void draw(void) override;
    void update(void) override;

    std::string get_roomname(void) const { return _roomname; };

private:
    TileAsset map_tile{ "graphics/tiles.png", SDL_Point{ 8, 8 } };

    std::string _roomname;
    SDL_Point room_pos;
};

class Room : public ScreenDrawable
{
public:
    Room(const JsonAsset& room_table, const TileAsset& tile_asset, SDL_Point room_pos);
    // TODO destroy blocks
    ~Room();

    void draw(void) override;
    void update(void) override;

    std::string name(void) const { return _name; }

    // TODO
    int blockCount(void) const;
    const std::vector<Block*>& blocks(void) {return _blocks;}


private:
    std::string _name;
    std::array<unsigned short, SURFACE_ARR_SIZE> _map_arr;

    std::vector<Block*> _blocks;
};
