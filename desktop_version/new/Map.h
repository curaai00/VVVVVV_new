#pragma once

#include "Room.h"

class Map
{
public:
    Map();
    virtual ~Map();

    Room *setRoom(const SDL_Point &room_pos);

private:
    Room *room = nullptr;
    TileAsset map_tile{"graphics/tiles.png", SDL_Point{8, 8}};
    JsonAsset room_table{"spacestation.json"};
};
