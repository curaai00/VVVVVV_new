#pragma once

#include "Drawable.h"
#include "Eventable.h"

#include <vector>

class Layer : public ScreenDrawable, public EventCompsitor
{
public:
    Layer(Type _type) : ScreenDrawable(_type), EventCompsitor()
    {
    }
    ~Layer()
    {
    }

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

    virtual void update(void) override
    {
        if (type() == Type::DYNAMIC)
            throw "Should implement update method on dynamic object";
        return;
    }

    // TODO: Need collision check after
    inline void addDrawable(Drawable *obj)
    {
        _objects.push_back(obj);
    }

private:
    std::vector<Drawable *> _objects;
};
