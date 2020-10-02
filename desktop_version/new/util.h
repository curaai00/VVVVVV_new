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
int len(std::string& str);

}; // namespace str

namespace sdl {
Uint32 ReadPixel(const SDL_Surface* _surface, int x, int y);
void DrawPixel(SDL_Surface* _surface, int x, int y, Uint32 pixel);
SDL_Color uint2color(const SDL_Surface* surface, const Uint32& c);
Uint32 color2uint(const SDL_Surface* surface, const SDL_Color& c);
void BlitSurfaceColoured(SDL_Surface* surface, const SDL_Color& c);

}; // namespace sdl

}; // namespace util
