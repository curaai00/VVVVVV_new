#pragma once

#include "Drawable.h"
#include "Eventable.h"

class Game
    : public EventCompsitor
    , public ScreenDrawable
{
public:
    Game()
        : EventCompsitor()
        , ScreenDrawable()
    {}
    virtual ~Game() {}

    virtual void update(void) = 0;

    void draw(void)
    {
        SDL_FillRect(_surface, NULL, 0);
        for (ScreenDrawable* layer : screen_layers) {
            layer->update();
            SDL_BlitSurface(layer->surface(), NULL, _surface, NULL);
        }
    }
    void key_event(const KeyPull& key_pull)
    {
        auto pressed_keys = key_pull.pressedKeys();
        for (auto k : pressed_keys)
            event(k);
    }

    SDL_Surface* surface(void) { return _surface; }

    void addScreenLayer(ScreenDrawable* screen) { screen_layers.push_back(screen); };

    enum class State
    {
        NONE,
        MENU,
        VVVVVV,
        PAUSED
    };
    State getState(void) { return _state; }
    void setState(State s) { _state = s; }

protected:
    std::vector<ScreenDrawable*> screen_layers;
    State _state = State::NONE;
};