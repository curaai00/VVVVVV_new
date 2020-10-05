#include "Map.h"
#include "Resource.h"

#include <SDL.h>
#include <array>

Map::Map(int roomx, int roomy)
{
    int rx, ry;
    rx = roomx;
    ry = roomy;
    rx -= 62;
    ry -= 64;

    room_pos = SDL_Point{ roomx, roomy };

    JsonAsset station{ "spacestation.json" };
    auto srx = std::to_string(rx);
    auto sry = std::to_string(ry);
    auto k = sry + srx;

    auto map_json_data = station.asset[k];
    _map_arr = map_json_data["content"]
                   .get<std::array<unsigned short, _map_arr_size>>();
    _roomname = map_json_data["roomname"].get<std::string>();
}