#pragma once

#include "Drawable.h"
#include "Resource.h"

#include <utf8/unchecked.h>

#include <string>

class Message : public ObjectDrawable
{
public:
    Message(SDL_Point xy, SDL_Color color, std::string msg);
    inline void draw(void) override {}

    const SDL_Point xy;
    const SDL_Color color;
    const std::string msg;

    TileAsset font_tile{ "graphics/font.png", SDL_Point{ 8, 8 } };

private:
    SDL_Rect tfont_rect{ 0, 0, 8, 8 }; // temp rect
};
