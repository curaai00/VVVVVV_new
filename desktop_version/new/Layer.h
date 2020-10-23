#pragma once

#include "Components/DrawableComponent.h"
#include "Components/DrawingComponents.h"
#include "Entity.h"

inline Entity *make_background(void) { ; }

class Layer : public Compositor<Entity, void>
{
public:
    Layer()
        : Compositor<Entity>(&Entity::update)
    {
        this->push(&_bottom_entity);

        _bottom_entity.push(new ClearComponent(surface()));
    }
    ~Layer() {}

    SDL_Surface *surface(void) { return screen.surface(); }

public:
    DrawableEntity _bottom_entity;
    StaticFullComponent screen;
};
