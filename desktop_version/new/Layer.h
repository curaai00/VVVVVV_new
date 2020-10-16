#pragma once

#include "Drawable.h"
#include "Eventable.h"

#include <vector>

class Layer : public ScreenDrawable, public EventCompsitor
{
public:
    Layer()
        : ScreenDrawable()
        , EventCompsitor()
    {
    }
    ~Layer() {}

    void draw_objects(void)
    {
        SDL_FillRect(_surface, NULL, 0x00000000);

        for (auto obj : _objects)
            obj->draw_to_parent(_surface);
    }

    virtual void update(void) = 0;

    // TODO: Need collision check after
    inline void addDrawable(Drawable *obj) { _objects.push_back(obj); }

private:
    std::vector<Drawable *> _objects;
};

class StaticLayer : public Layer
{
public:
    StaticLayer()
        : Layer()
    {
    }
    ~StaticLayer() {}

    virtual void update(void) override { return; }
};