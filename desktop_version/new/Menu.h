#pragma once

#include "Background.h"
#include "Game.h"
#include "Message.h"
#include "Sprite.h"

class Menu : public Game
{
public:
    Menu()
    {
        StaticLayer *intro_layer = new StaticLayer();
        intro_layer->addDrawable(&titleSprite);
        intro_layer->addDrawable(&msg);

        addLayer(&back);
        addLayer(intro_layer);

        // addEventable(&event_ctrl);
    }
    ~Menu() {}

    void update(void)
    {
        for (Layer *layer : screen_layers)
            layer->update();
    }

private:
    IntroBackground back;
    Message msg{SDL_Point{5, 175}, SDL_Color{255, 0, 0, 255},
                "[ Press ACTION to Start ]", true};
    // 23 is sprite idx of Big V
    SpriteSet titleSprite{SDL_Point{64, 50},
                          {23, 23, 23, 23, 23, 23}};
};
