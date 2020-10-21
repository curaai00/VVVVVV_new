#pragma once

#include "Components/DrawableComponent.h"
#include "Components/DrawingComponents.h"
#include "Entity.h"

inline Entity *make_background(void) { ; }

class Layer : Compositor<Entity, void, &Entity::update>
{
public:
    Layer()
        : Compositor<Entity, void, &Entity::update>()
    {
        add(&clear);
        add(&screen);
    }
    ~Layer() {}

    SDL_Surface *surface(void) { return screen.surface(); }

public:
    FullScreenComponent screen;
    ClearComponent clear(screen->surface());
};
