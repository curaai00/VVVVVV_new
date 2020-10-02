#pragma once

#include "Drawable.h"
#include "Eventable.h"

#include <vector>

class Layer
    : public ScreenDrawable
    , public EventCompsitor
{
public:
    Layer(){};
    ~Layer(){};

    inline virtual void draw(void) override
    {
        SDL_FillRect(_surface, NULL, 0x00000000);

        for (auto obj : _objects) {
            obj->draw();
            auto draw_rect = obj->getDrawRect();
            auto draw_surface = obj->getSurface();
            SDL_BlitSurface(draw_surface, NULL, _surface, &draw_rect);
        }
    }

    // TODO: Need collision check after
    inline void addDrawable(ObjectDrawable* obj) { _objects.push_back(obj); }

private:
    std::vector<ObjectDrawable*> _objects;
};
