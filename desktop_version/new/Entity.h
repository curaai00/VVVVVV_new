#pragma once

#include "Components/Component.h"
#include <vector>

// using Entity = Compositor<Component>;
class Entity : public Compositor<Component, void>
{
public:
    Entity(void)
        : Compositor<Component>(&Component::update)
    {
    }
};

class DrawableEntity : public Entity
{
public:
    DrawableEntity(void)
        : Entity()
    {
    }
    void set_surface(SDL_Surface *surface) { _surface = surface; }
    SDL_Surface *surface(void) { return _surface; }

protected:
    SDL_Surface *_surface;
};