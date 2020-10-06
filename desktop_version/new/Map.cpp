#include "Map.h"

Map::Map() {}
Map::~Map()
{
    if (room)
        delete room;
}

void Map::setRoom(const SDL_Point& room_pos)
{
    if (room)
        delete room;

    room = new Room(room_table, map_tile, room_pos);
}

void Map::draw(void)
{
    if (room) {
        room->draw();
        SDL_BlitSurface(room->surface(), NULL, _surface, NULL);
    }
}

void Map::update(void)
{
    if (room)
        room->update();
}
