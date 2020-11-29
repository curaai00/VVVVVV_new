#pragma once

#include "Character.h"
#include "Room.h"
#include "Scene.h"

class Game : public Scene
{
public:
    Game()
        : Scene(State::GAME)
    {
        set_room(new Room{SDL_Point{114, 105}});
        character = new Character{{290, 162}};
        room->set_character(character);
        EventEntities::push(character);
    }
    ~Game();

    void set_room(Room *_room)
    {
        if (room != nullptr) delete Layers::pop(room);
        room = _room;
        Layers::push(_room);
    }

private:
    Character *character = nullptr;
    Room *room = nullptr;
};