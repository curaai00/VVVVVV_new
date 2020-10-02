#pragma once

#include "Drawable.h"
#include "Eventable.h"
#include "Resource.h"

#include <SDL.h>

#include <array>
#include <vector>

class Background
    : public Eventable
    , public ScreenDrawable
{
public:
    Background();
    ~Background();

    void draw(void) override;
    void scroll(void);

    bool event(const SDL_Keycode k) override;

    JsonAsset towerdata{ "tower.json" };
    TileAsset colortile{ "graphics/tiles3.png", SDL_Point{ 8, 8 } };

    std::vector<unsigned short> tower;

    unsigned int getColor(void) const;
    void setColor(void);
    void setColor(unsigned int c);

private:
    unsigned int _color = 0;
    unsigned int _scroll_start_y = 0;
};
