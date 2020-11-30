#pragma once

#include "Character.h"
#include "Components/GravityComponent.h"
#include "Room.h"
#include "Scene.h"

class Game : public Scene
{
public:
    Game()
        : Scene(State::GAME)
    {
        character = new Character{{290, 162}};
        // character = new Character{{290, 106}};
        EventEntities::push(character);

        set_room(SDL_Point{114, 105});
    }
    ~Game();

    // TODO: interate with blocks
    void set_room(SDL_Point room_pos)
    {
        if (back_room != nullptr) delete Layers::pop(back_room);
        back_room = new Room{room_pos, EBlockType::BACK};
        Layers::push(back_room);

        if (fore_room != nullptr) delete Layers::pop(fore_room);
        fore_room = new Room{room_pos, EBlockType::FORE};
        Layers::push(fore_room);
        fore_room->set_character(character);

        fore_room->update();
    }

private:
    Character *character = nullptr;
    Room *fore_room = nullptr;
    Room *back_room = nullptr;
};