#pragma once

#include "Block.h"
#include "Character.h"
#include "Components/GraphicComponents.h"
#include "Layer.h"
#include "Message.h"
#include "Resource.h"

#include <array>
#include <string>

// TODO: Room can dyanmic, but temporary set static for short refac
class Room : public Layer
{
private:
    class RoomEnterComponnet : public GraphicComponent
    {
    public:
        RoomEnterComponnet(const std::string &roomname)
            : GraphicComponent()
            , _roomname(roomname)
        {
            auto fill_black = [](SDL_Surface *surface) {
                auto c = util::sdl::color2uint(surface, {0, 0, 0, 255});
                SDL_FillRect(surface, NULL, c);
            };
            auto draw_msg = [&roomname](SDL_Surface *surface) {
                Message msg{{0, 1}, {255, 255, 255, 255}, roomname, true};
                msg.draw_to_parent(surface);
            };

            _surface = util::sdl::CreateSurface({320, 10});
            _draw_rect = SDL_Rect{0, 230, 320, 10};

            fill_black(_surface);
            draw_msg(_surface);
        }

    private:
        std::string _roomname;
    };

public:
    Room(const JsonAsset &room_table, const TileAsset &tile_asset,
         SDL_Point room_pos);
    ~Room();
    Room(const Room &room) = delete;
    Room &operator=(const Room &room) = delete;

    virtual void update(void) override;

    Character *character() { return _character; }
    std::string name(void) const { return _name; }
    int blockCount(void) const { return static_cast<int>(_blocks.size()); };
    const std::vector<Block *> &blocks(void) { return _blocks; }

private:
    SDL_Point _room_pos;
    std::string _name;

    std::array<unsigned short, SURFACE_ARR_SIZE> _cell_arr;
    std::vector<Block *> _blocks;
    RoomEnterComponnet *_roomenter;

    Character *_character;
};
