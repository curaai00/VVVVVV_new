#pragma once

#include <SDL.h>
#include <string>

#ifndef SDL_BYTE_MASK
#define SDL_BYTE_MASK
const uint32_t R_MASK = 0x000000ff;
const uint32_t G_MASK = 0x0000ff00;
const uint32_t B_MASK = 0x00ff0000;
const uint32_t A_MASK = 0xff000000;
#endif

namespace util {
namespace str {
bool endsWith(const std::string& str, const std::string& suffix);

}; // namespace str

namespace sdl {
Uint32 ReadPixel(SDL_Surface* _surface, int x, int y);
void DrawPixel(SDL_Surface* _surface, int x, int y, Uint32 pixel);
void BlitSurfaceColoured(SDL_Surface* _src,
                         SDL_Rect* _srcRect,
                         SDL_Surface* _dest,
                         SDL_Rect* _destRect,
                         SDL_Color& ct);

}; // namespace sdl

}; // namespace util
