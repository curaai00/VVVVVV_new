#pragma once

#include "Components/BackgroundComponent.h"
#include "Game.h"

class Menu : public Game
{
public:
    Menu()
        : Game(State::MENU)
    {
        // this->push(&back_layer);
        back_layer.push(&back_entity);
        back_entity.push(new StripeComponent);

        this->push(&msg_layer);
        auto msg_entity = new DrawableEntity{};
        std::string asf{"[Press ACTION to Start]"};
        auto msg_cmpt = new MessageComponent{font_asset, asf, true};
        msg_entity->set_drawable();
        msg_entity->push(msg_cmpt);
        msg_entity->push(
            new DrawToComponent{msg_entity->drawable(), msg_layer.drawable()});
        msg_layer.push(msg_entity);
    }

    ~Menu() {}

protected:
    TileAsset font_asset{"graphics/font.png", SDL_Point{8, 8}};

    DrawableEntity back_entity;
    Layer back_layer;
    Layer msg_layer;
};
