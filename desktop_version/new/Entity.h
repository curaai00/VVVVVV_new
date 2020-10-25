#pragma once

#include "Components/Component.h"
#include "Drawable.h"
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
    ~Entity(void)
    {
        for (auto component : _elements)
            delete component;
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

    void set_drawable(Drawable drawable) { _drawable = drawable; }
    const Drawable &drawable(void) { return _drawable; }
    SDL_Surface *surface(void) { return _drawable.surface; }
    SDL_Rect rect(void) const { return _drawable.rect; }

protected:
    Drawable _drawable;
};
