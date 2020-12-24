#pragma once

#include "Components/Drawable/BlockComponent.h"
#include "Components/DrawableComponent.h"
#include "Components/DynamicDrawingComponent.h"
#include "Events/GravityEvent.h"

#include "Character.h"
#include "Layer.h"
#include "util.h"

// TODO: Think how about inheritance instead of blocktype
class Room : public Layer
{
public:
    Room(const std::string &name, EBlockType _blocks_type)
        : Room(str2pos(name), _blocks_type)
    {
    }
    Room(const SDL_Point &pos, EBlockType _blocks_type)
        : _blocks_type(_blocks_type)
    {
        auto cvt2key = [](const SDL_Point &pos) -> std::string {
            auto rx = pos.x - 62;
            auto ry = pos.y - 64;
            return std::to_string(ry) + std::to_string(rx);
        };

        auto roomdata = _room_table.asset[cvt2key(pos)];
        _name = roomdata["roomname"].get<std::string>();
        _cells = roomdata["content"].get<Cells>();

        auto blocks = block_factory(_cells, _block_tile, _blocks_type);
        for (auto block : blocks)
            push_drawable_component(block);
    }

    void set_character(Character *character)
    {
        character->generate_collision_component(surface());

        character->Entity::push(
            new DynamicDrawToComponent{character->drawable(), drawable().surface});
        push(character);
    }

    SDL_Point str2pos(const std::string &name) { throw NotImplementedError(); }

    std::string name(void) { return _name; }

private:
    EBlockType _blocks_type;
    TileAsset _block_tile{"graphics/tiles.png", SDL_Point{8, 8}};
    JsonAsset _room_table{"spacestation.json"};

    std::string _name;
    Cells _cells;
};
