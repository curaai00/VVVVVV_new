#pragma once

#include "Components/Drawable/BlockComponent.h"
#include "Components/DrawableComponent.h"

#include "Character.h"
#include "Layer.h"
#include "util.h"

class Room : public Layer
{
public:
    Room(const std::string &name)
        : Room(str2pos(name))
    {
    }
    Room(const SDL_Point &pos)
    {
        auto cvt2key = [](const SDL_Point &pos) -> std::string {
            auto rx = pos.x - 62;
            auto ry = pos.y - 64;
            return std::to_string(ry) + std::to_string(rx);
        };

        auto roomdata = _room_table.asset[cvt2key(pos)];
        _name = roomdata["roomname"].get<std::string>();
        _cells = roomdata["content"].get<Cells>();

        push_drawable_component(new WallComponent{_cells, _block_tile});
        push_drawable_component(new ThornComponent{_cells, _block_tile});
        push_drawable_component(new BackWallComponent{_cells, _block_tile});
    }

    void set_character(Character *character)
    {
        character->Entity::push(
            new DrawToComponent{character->drawable(), drawable()});
        push(character);
    }

    SDL_Point str2pos(const std::string &name) { throw NotImplementedError(); }

    std::string name(void) { return _name; }

private:
    TileAsset _block_tile{"graphics/tiles.png", SDL_Point{8, 8}};
    JsonAsset _room_table{"spacestation.json"};

    std::string _name;
    Cells _cells;
};