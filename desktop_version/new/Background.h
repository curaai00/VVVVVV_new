#pragma once

#include "Resource.h"

#include "SDL.h"
#include <array>
#include <vector>

class Background
{
public:
    Background();

    void draw(void);
    void scroll(void);

    JsonAsset towerdata{ "tower.json" };
    PNGAsset colortile{ "graphics/tiles3.png" };

    std::vector<unsigned short> tower;
    SDL_Surface* surface;
    std::vector<SDL_Surface*> tiles;

private:
    unsigned int scroll_start_y = 0;
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
    // SDL_Surface* subSurface = SDL_DisplayFormatAlpha(preSurface);

    // SDL_FreeSurface(preSurface);

    // Lastly, apply the area from the meta _surface onto the whole of the sub
    // _surface.
    SDL_BlitSurface(metaSurface, &area, preSurface, 0);

    // Return the new Bitmap _surface
    return preSurface;
}