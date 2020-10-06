#pragma once

#include "Room.h"

class Map : public ScreenDrawable
{
public:
    Map();
    virtual ~Map();

    void setRoom(const SDL_Point& room_pos);

    void draw(void) override;
    void update(void) override;

private:
    Room* room = nullptr;
    TileAsset map_tile{ "graphics/tiles.png", SDL_Point{ 8, 8 } };
    JsonAsset room_table{ "spacestation.json" };
};
