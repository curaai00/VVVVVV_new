#pragma once

#include "Components/DrawableComponent.h"
#include "Components/DrawingComponent.h"
#include "Entity.h"

class Layer : public Compositor<Entity, void>
{
public:
    Layer()
        : Compositor<Entity>(&Entity::update)
    {
        _bottom_entity = new DrawableEntity{};
        this->push(_bottom_entity);

        _bottom_entity->push(new ClearComponent(surface()));
    }
    ~Layer()
    {
        for (auto entity : _elements)
            delete entity;
    }

    void push_drawable_component(DrawableComponent *cpnt)
    {
        push_drawable_entity(make_drawable_entity(cpnt));
    }

    void push_drawable_entity(DrawableEntity *entity)
    {
        entity->push(new DrawToComponent{entity->drawable(), drawable()});
        push(entity);
    }

    SDL_Surface *surface(void) { return screen.surface(); }
    const Drawable &drawable(void) { return screen.drawable(); }

public:
    DrawableEntity *_bottom_entity;
    StaticFullComponent screen;
};
