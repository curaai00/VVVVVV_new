#pragma once

#include "Resource.h"

#include "Eventable.h"
#include "SDL.h"

#include <array>
#include <vector>

class Background : public Eventable
{
public:
    Background();
    ~Background();

    void draw(void);
    void scroll(void);

    bool event(const SDL_Keycode k) override;

    JsonAsset towerdata{ "tower.json" };
    PNGAsset colortile{ "graphics/tiles3.png" };

    std::vector<unsigned short> tower;
    SDL_Surface* surface;
    std::vector<SDL_Surface*> tiles;

    unsigned int getColor(void) const;
    void setColor(void);
    void setColor(unsigned int c);

private:
    unsigned int _color = 0;
    unsigned int _scroll_start_y = 0;
};

inline SDL_Surface* GetSubSurface(SDL_Surface* metaSurface, SDL_Rect area)
{
    // we will slow things down.
    SDL_Surface* preSurface =
        SDL_CreateRGBSurface(SDL_SWSURFACE,
                             area.w,
                             area.h,
                             metaSurface->format->BitsPerPixel,
                             metaSurface->format->Rmask,
                             metaSurface->format->Gmask,
                             metaSurface->format->Bmask,
                             metaSurface->format->Amask);
    SDL_BlitSurface(metaSurface, &area, preSurface, 0);

    return preSurface;
}