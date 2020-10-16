#pragma once

#include "Background.h"
#include "Character.h"
#include "Game.h"
#include "Map.h"

class VVVVVV : public Game
{
public:
    VVVVVV();
    virtual ~VVVVVV();

    void update(void) override;

private:
    SpaceBackground spacebackground;
    Map map;
    Room *room;
    Character *player;
};
