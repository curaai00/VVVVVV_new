#pragma once

#include <SDL.h>
#include <string>

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
