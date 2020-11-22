#pragma once

#include "Components/BackgroundComponent.h"
#include "Game.h"

class Menu : public Game
{
public:
    Menu()
        : Game(State::MENU)
    {
        back_layer.push(&back_entity);
        back_entity.push(new StripeComponent);

        this->push(&msg_layer);
        auto msg_entity = new DrawableEntity{};
        msg_entity->add_drawable_component(
            new MessageComponent{{5, 175}, "[Press ACTION to Start]", true});

        auto title_entity = new DrawableEntity{};
        util::sdl::FlipStatus fs;
        auto spr_cmpt = new SpriteComponent{
            {64, 50}, {23, 23, 23, 23, 23, 23}, {fs, fs, fs, fs, fs, fs}};
        title_entity->add_drawable_component(spr_cmpt);

        msg_layer.push_drawable_entity(msg_entity);
        msg_layer.push_drawable_entity(title_entity);
    }

    ~Menu() {}

protected:
    DrawableEntity back_entity;
    Layer back_layer;
    Layer msg_layer;
};
