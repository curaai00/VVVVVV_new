#pragma once

#include "Components/Component.h"
#include <vector>

// using Entity = Compositor<Component>;
class Entity : public Compositor<Component, void>
{
public:
    Entity(const std::vector<Component *> &components)
        : Entity()
    {
    }
    Entity(void)
        : Compositor<Component>(&Component::update)
    {
    }
};

class DrawableEntity : public Entity
{
public:
    DrawableEntity(const std::vector<Component *> &components)
        : Entity(components)
    {
    }
    DrawableEntity()
        : Entity()
    {
    }

    void set_surface(SDL_Surface *surface) { _surface = surface; }
    void set_rect(const SDL_Rect &rect) { _rect = rect; }
    SDL_Surface *surface(void) { return _surface; }
    SDL_Rect rect(void) const { return _rect; }

protected:
    SDL_Surface *_surface;
    SDL_Rect _rect;
};