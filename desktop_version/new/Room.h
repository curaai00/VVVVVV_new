#pragma once

#include "Block.h"
#include "Component.h"
#include "Layer.h"
#include "Message.h"
#include "Resource.h"

#include <array>
#include <string>

class RoomEnterComponnet : public Component
{
public:
    RoomEnterComponnet(const std::string& roomname)
        : Component(util::sdl::CreateSurface({320, 10}), SDL_Rect{ 0, 230, 320, 10 }, Type::STATIC)
        , _roomname(roomname)
    {
        auto c = util::sdl::color2uint(_surface, {0, 0, 0, 255});
        SDL_FillRect(_surface, NULL, c);

        Message msg{ { 0, 1 }, { 255, 255, 255, 255 }, roomname, true };
        auto rect = msg.rect();
        SDL_BlitSurface(msg.surface(), NULL, _surface, &rect);
    }
    void update(void) override {return;}

private:
    std::string _roomname;
};

// TODO:Room can dyanmic, but temporary set static for short refac
class Room : public Layer
{
public:
    Room(const JsonAsset& room_table, const TileAsset& tile_asset, SDL_Point room_pos);
    ~Room();
    Room(const Room& room) = delete;
    Room& operator=(const Room& room) = delete;

    std::string name(void) const { return _name; }

    int blockCount(void) const { return static_cast<int>(_blocks.size()); };
    const std::vector<Block*>& blocks(void) { return _blocks; }

private:
    SDL_Point _room_pos;
    std::string _name;

    std::array<unsigned short, SURFACE_ARR_SIZE> _cell_arr;
    std::vector<Block*> _blocks;
    RoomEnterComponnet* _roomenter;
};
