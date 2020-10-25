#pragma once

#include "Components/DrawableComponent.h"
#include "Layer.h"

class Game : public Compositor<Layer, void>
{
public:
    enum class State
    {
        MENU,
        GAME,
        PAUSED
    };

    Game(State state)
        : Compositor<Layer>(&Layer::update)
        , _state(state)
    {
        clear = new ClearComponent{screen.surface()};
    }
    ~Game() { delete clear; };

    SDL_Surface *surface(void)
    {
        clear->update();
        for (Layer *layer : _elements)
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
