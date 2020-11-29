#pragma once

#include "Components/DrawableComponent.h"
#include "Layer.h"

class Scene : public Compositor<Layer, void>,
              public Compositor<EventEntity, SDL_Keycode>
{
public:
    using Layers = Compositor<Layer, void>;
    using EventEntities = Compositor<EventEntity, SDL_Keycode>;

    enum class State
    {
        MENU,
        GAME,
        PAUSED
    };

    Scene(State state)
        : Compositor<Layer>(&Layer::update)
        , Compositor<EventEntity, SDL_Keycode>(&EventEntity::update)
        , _state(state)
    {
        clear = new ClearComponent{screen.surface()};
    }
    ~Scene() { delete clear; };

    SDL_Surface *surface(void)
    {
        clear->update();
        for (Layer *layer : Layers::_elements)
            SDL_BlitSurface(layer->surface(), NULL, screen.surface(), NULL);
        return screen.surface();
    }

    State state(void) const { return _state; }

private:
    ClearComponent *clear;

protected:
    StaticFullComponent screen;
    const State _state;
};
