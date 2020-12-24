#pragma once

#include "Components/Component.h"
#include "Components/DrawableComponent.h"
#include "Components/DrawingComponent.h"
#include "Drawable.h"
#include "Events/Event.h"
#include "utils/Compositor.h"

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

    void add_drawable_component(DrawableComponent *cmpt)
    {
        _drawable = cmpt->drawable();
        push(cmpt);
    }
    void set_color(const SDL_Color &color)
    {
        if (_drawable.surface == nullptr) throw "DrawableEntity: Set drawable first";

        push(new ColorComponent{_drawable.surface, color});
    }

    const Drawable &drawable(void) { return _drawable; }
    SDL_Surface *surface(void) { return _drawable.surface; }
    SDL_Rect rect(void) const { return _drawable.rect; }

protected:
    Drawable _drawable;
};

class AnimatableEntity : public Entity
{
public:
    AnimatableEntity()
        : Entity()
    {
        _drawable = new Drawable{};
    }
    virtual ~AnimatableEntity() { delete _drawable; }

    Drawable *drawable(void) { return _drawable; }
    SDL_Surface *surface(void) { return _drawable->surface; }
    SDL_Rect rect(void) const { return _drawable->rect; }

protected:
    Drawable *_drawable;
};

inline DrawableEntity *make_drawable_entity(DrawableComponent *comp)
{
    auto ent = new DrawableEntity{};
    ent->add_drawable_component(comp);
    return ent;
}

class EventEntity : public Compositor<Event, SDL_Keycode>
{
public:
    EventEntity(const std::vector<Event *> &evts)
        : EventEntity()
    {
    }
    EventEntity(void)
        : Compositor<Event, SDL_Keycode>(&Event::update)
    {
    }
};
