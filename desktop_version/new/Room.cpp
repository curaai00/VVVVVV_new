#include "Room.h"

Room::Room(const JsonAsset& room_table, const TileAsset& tile_asset, SDL_Point room_pos)
    : Layer(Type::STATIC)
{
    int rx, ry;
    rx = room_pos.x;
    ry = room_pos.y;
    rx -= 62;
    ry -= 64;
    auto srx = std::to_string(rx);
    auto sry = std::to_string(ry);

    _room_pos = SDL_Point{ rx, ry };
    auto map_json_data = room_table.asset[sry + srx];
    _cell_arr =
        map_json_data["content"].get<std::array<unsigned short, SURFACE_ARR_SIZE>>();
    _name = map_json_data["roomname"].get<std::string>();

    _roomenter = new RoomEnterComponnet{ _name };

    _blocks.push_back(new Wall{ _cell_arr, tile_asset });
    _blocks.push_back(new Thorn{ _cell_arr, tile_asset });
    _blocks.push_back(new BackWall{ _cell_arr, tile_asset });

    for (auto block : _blocks)
        addDrawable(block);

    draw_objects();
    _roomenter->draw_to_parent(_surface);
    
}

Room::~Room()
{
    for (Block* b : _blocks)
        if (b != nullptr)
            delete b;
    _blocks.clear();
    delete _roomenter;
}
