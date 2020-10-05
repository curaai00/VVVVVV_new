#pragma once

#include "Drawable.h"
#include "Resource.h"
#include <array>
#include <string>

class Map : public ScreenDrawable
{
public:
    Map(int roomx, int roomy);
    virtual ~Map();
    void draw(void) override;
    void update(void) override;

    std::string get_roomname(void) const { return _roomname; };

private:
    static constexpr int _map_arr_size = 1200;
    std::array<unsigned short, _map_arr_size> _map_arr;
    TileAsset map_tile{ "graphics/tiles.png", SDL_Point{ 8, 8 } };

    std::string _roomname;
    SDL_Point room_pos;
};
