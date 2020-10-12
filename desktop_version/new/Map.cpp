#include "Map.h"

Map::Map()
{
}
Map::~Map()
{
    if (room)
        delete room;
}

Room *Map::setRoom(const SDL_Point &room_pos)
{
    if (room)
        delete room;

    room = new Room(room_table, map_tile, room_pos);
    return room;
}
