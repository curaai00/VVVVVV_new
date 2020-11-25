#pragma once

#include "Components/BackgroundComponent.h"
#include "Scene.h"

class Menu : public Scene
{
public:
    Menu()
        : Scene(State::MENU)
    {
        back_layer = new Layer;
        push(back_layer);
        auto stripe_entity = make_drawable_entity(new StripeComponent);
        back_layer->push_drawable_entity(stripe_entity);

        title_layer = new Layer;
        push(title_layer);
        title_layer->push_drawable_component(
            new SpriteComponent{{64, 50}, std::vector<unsigned int>(6, 23)});

        title_layer->push_drawable_component(
            new MessageComponent{{5, 175}, "[Press ACTION to Start]", true});
    }

    ~Menu() {}

protected:
    Layer *back_layer;
    Layer *title_layer;
};
