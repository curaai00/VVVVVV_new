#pragma once

#include "Component.h"
#include "Drawable.h"
#include "Resource.h"

#include <utf8/unchecked.h>

#include <string>

class Message : public Drawable
{
public:
    Message(SDL_Point xy, SDL_Color color, std::string msg, bool center = false);
    ~Message();
    Message &operator=(const Message &) = delete; // Disallow copying
    Message(const Message &) = delete;

    void update(void) override
    {
        return;
    };

    SDL_Point xy;
    SDL_Color color;
    const std::string msg;

    TileAsset font_tile{"graphics/font.png", SDL_Point{8, 8}};

private:
    SDL_Rect tfont_rect{0, 0, 8, 8}; // temp rect
    ColorComponent *_color;
};
