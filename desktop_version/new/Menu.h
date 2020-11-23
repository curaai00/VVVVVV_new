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

        this->push(&title_layer);

        auto spr_entity = make_drawable_entity(
            new SpriteComponent{{64, 50}, std::vector<unsigned int>(6, 23)});
        title_layer.push_drawable_entity(spr_entity);

        auto title_entity = make_drawable_entity(
            new MessageComponent{{5, 175}, "[Press ACTION to Start]", true});
        title_layer.push_drawable_entity(title_entity);
    }

    ~Menu() {}

protected:
    DrawableEntity back_entity;
    Layer back_layer;
    Layer title_layer;
};
