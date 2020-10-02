#include "util.h"
#include <utf8/unchecked.h>

using namespace util::str;
using namespace util::sdl;

int util::str::len(std::string& str)
{
    int bfontpos = 0;
    std::string::iterator iter = str.begin();
    while (iter != str.end()) {
        int cur = utf8::unchecked::next(iter);
        bfontpos += cur < 32 ? 6 : 8;
    }
    return bfontpos;
}

bool util::str::endsWith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() &&
           0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

Uint32 util::sdl::ReadPixel(const SDL_Surface* _surface, int x, int y)
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

Uint32 util::sdl::color2uint(const SDL_Surface* surface, const SDL_Color& c)
{
    Uint32 u_color;
    auto get_shift_size = [](Uint32 mask) -> unsigned int {
        for (int i = 0; i < 32; i++)
            if (mask & 1 << i)
                return i;
        throw "Invalid pixel mask";
    };

    const SDL_PixelFormat& fmt = *(surface->format);
    u_color |= c.a << get_shift_size(fmt.Amask);
    u_color |= c.r << get_shift_size(fmt.Rmask);
    u_color |= c.g << get_shift_size(fmt.Gmask);
    u_color |= c.b << get_shift_size(fmt.Bmask);
    return u_color;
}

SDL_Color util::sdl::uint2color(const SDL_Surface* surface, const Uint32& c)
{
    const SDL_PixelFormat& fmt = *(surface->format);
    SDL_Color color;
    color.a = fmt.Amask & c;
    color.r = fmt.Rmask & c;
    color.g = fmt.Gmask & c;
    color.b = fmt.Bmask & c;
    return color;
}

void util::sdl::BlitSurfaceColoured(SDL_Surface* surface, const SDL_Color& c)
{
    const SDL_PixelFormat& fmt = *(surface->format);
    auto u_color = color2uint(surface, c);

    for (int x = 0; x < surface->w; x++)
        for (int y = 0; y < surface->h; y++)
            if (ReadPixel(surface, x, y) & fmt.Amask)
                DrawPixel(surface, x, y, u_color);
}