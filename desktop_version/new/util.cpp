#include "util.h"

using namespace util::str;
using namespace util::sdl;

bool util::str::endsWith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
           0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

Uint32 util::sdl::ReadPixel(SDL_Surface* _surface, int x, int y)
{
    int bpp = _surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8* p = (Uint8*)_surface->pixels + y * _surface->pitch + x * bpp;

    switch (bpp) {
        case 1:
            return *p;
            break;

        case 2:
            return *(Uint16*)p;
            break;

        case 3:
            return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32*)p;
            break;

        default:
            return 0; /* shouldn't happen, but avoids warnings */
    }
}

void util::sdl::DrawPixel(SDL_Surface* _surface, int x, int y, Uint32 pixel)
{
    int bpp = _surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8* p = (Uint8*)_surface->pixels + y * _surface->pitch + x * bpp;

    switch (bpp) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16*)p = pixel;
            break;

        case 3:
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
            break;

        case 4:
            *(Uint32*)p = pixel;
            break;
    }
}

void util::sdl::BlitSurfaceColoured(SDL_Surface* _src,
                                    SDL_Rect* _srcRect,
                                    SDL_Surface* _dest,
                                    SDL_Rect* _destRect,
                                    SDL_Color& ct)
{
    SDL_Rect* tempRect = _destRect;

    const SDL_PixelFormat& fmt = *(_src->format);
    // const SDL_PixelFormat& destfmt = *(_dest->format);

    SDL_Surface* tempsurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                                    _src->w,
                                                    _src->h,
                                                    fmt.BitsPerPixel,
                                                    fmt.Rmask,
                                                    fmt.Gmask,
                                                    fmt.Bmask,
                                                    fmt.Amask);

    for (int x = 0; x < tempsurface->w; x++) {
        for (int y = 0; y < tempsurface->h; y++) {
            Uint32 pixel = ReadPixel(_src, x, y);
            Uint32 Alpha = pixel & fmt.Amask;
            Uint32 result = *((Uint32*)&ct) & 0x00FFFFFF;
            Uint32 CTAlpha = *((Uint32*)&ct) & fmt.Amask;
            float div1 = ((Alpha >> 24) / 255.0f);
            float div2 = ((CTAlpha >> 24) / 255.0f);
            Uint32 UseAlpha = (div1 * div2) * 255.0f;
            DrawPixel(tempsurface, x, y, result | (UseAlpha << 24));
        }
    }

    SDL_BlitSurface(tempsurface, _srcRect, _dest, tempRect);
    SDL_FreeSurface(tempsurface);
}