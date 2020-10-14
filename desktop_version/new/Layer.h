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
        {
            auto draw_rect = obj->rect();
            auto draw_surface = obj->surface();
            SDL_BlitSurface(draw_surface, NULL, _surface, &draw_rect);
        }
    }

    virtual void update(void) { return; }

    // TODO: Need collision check after
    inline void addDrawable(Drawable *obj)
    {
        _objects.push_back(obj);
    }

private:
    std::vector<Drawable *> _objects;
};
