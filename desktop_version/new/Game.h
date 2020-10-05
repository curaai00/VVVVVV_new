#pragma once

#include "Drawable.h"
#include "Eventable.h"

class Game : public EventCompsitor
{
public:
    Game()
    {
        surface = SDL_CreateRGBSurface(
            0, 320, 240, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    }
    virtual ~Game()
    {
        if (surface)
            SDL_FreeSurface(surface);
    }

    virtual void update(void) = 0;

    void draw(void)
    {
        SDL_FillRect(surface, NULL, 0);
        for (ScreenDrawable* layer : screen_layers) {
            layer->draw();
            SDL_BlitSurface(layer->getSurface(), NULL, surface, NULL);
        }
    }
    void key_event(const KeyPull& key_pull)
    {
        auto pressed_keys = key_pull.pressedKeys();
        for (auto k : pressed_keys)
            event(k);
    }

    SDL_Surface* getSurface(void) { return surface; }

    void addScreenLayer(ScreenDrawable* screen)
    {
        screen_layers.push_back(screen);
    };

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
    SDL_Surface* surface;
    State _state = State::NONE;
};