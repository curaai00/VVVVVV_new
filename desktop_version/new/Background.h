#pragma once

#include "Resource.h"

#include <SDL.h>
#include <array>
#include <vector>

class Background
{
public:
    Background();

    void draw(void);

    JsonAsset towerdata{ "tower.json" };
    PNGAsset colortile{ "graphics/tile3.png" };

    // std::array<unsigned short, 4800> tower;
    std::vector<unsigned short> tower;
    SDL_Surface* surface;
    std::vector<SDL_Surface*> tiles;
};

inline SDL_Surface* GetSubSurface(SDL_Surface* metaSurface,
                                  int x,
                                  int y,
                                  int width,
                                  int height)
{
    // Create an SDL_Rect with the area of the _surface
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.w = width;
    area.h = height;

    // Convert to the correct display format after nabbing the new _surface or
    // we will slow things down.
    SDL_Surface* preSurface =
        SDL_CreateRGBSurface(SDL_SWSURFACE,
                             width,
                             height,
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