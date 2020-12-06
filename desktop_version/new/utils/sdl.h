#pragma once

#include "../Drawable.h"
#include "../util.h"
#include <set>

inline SDL_Point operator+(SDL_Point const &a, SDL_Point const &b)
{
    return {a.x + b.x, a.y + b.y};
    // return a.x == b.x && a.y == b.y;
}
inline bool operator==(SDL_Point const &a, SDL_Point const &b)
{
    return a.x == b.x && a.y == b.y;
}
inline bool operator<(SDL_Point const &a, SDL_Point const &b)
{
    if (a.x > b.x)
        return true;
    else if (a.x == b.x)
        return a.y > b.y;
    else
        return false;
}

namespace util
{
namespace sdl
{
struct FlipStatus
{
    bool vertical;
    bool horizontal;
};

SDL_Surface *create(const SDL_Point &rect);
void destroy(SDL_Surface *surface);

void copyTo(SDL_Surface *src, SDL_Surface *dst);
SDL_Surface *copy(SDL_Surface *src);

void blit(SDL_Surface *src, const SDL_Rect *src_r, SDL_Surface *dst,
          const SDL_Rect *dst_r);
SDL_Surface *patch(SDL_Surface *src, const SDL_Rect &rect);

Uint32 getPixel(const SDL_Surface *_surface, int x, int y);
void setPixel(SDL_Surface *_surface, int x, int y, Uint32 pixel);

SDL_Color uint2color(const SDL_Surface *surface, const Uint32 &c);
Uint32 color2uint(const SDL_Surface *surface, const SDL_Color &c);
void fillColor(SDL_Surface *surface, const SDL_Color &c);

bool cmpColor(const SDL_Color &a, const SDL_Color &b);
bool cmpPos(const SDL_Point &a, const SDL_Point &b);
bool cmpRect(const SDL_Rect &a, const SDL_Rect &b);

SDL_Rect getTightRect(const SDL_Surface *surface);
SDL_Surface *rotate(SDL_Surface *surf, FlipStatus flip);

bool collision_check(const SDL_Surface *screen, const Drawable &drawble);
std::set<SDL_Point> boundary(const SDL_Surface *surface);

}; // namespace sdl

}; // namespace util

using FlipStatus = util::sdl::FlipStatus;