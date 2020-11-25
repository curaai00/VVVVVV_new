#pragma once

#include "Room.h"
#include "Scene.h"

class Game : public Scene
{
public:
    Game()
        : Scene(State::GAME)
    {
        set_room(new Room{SDL_Point{114, 105}});
    }
    ~Game();

    void set_room(Room *_room)
    {
        if (room != nullptr) delete pop(room);
        room = _room;
        push(_room);
    }

private:
    Room *room = nullptr;
};