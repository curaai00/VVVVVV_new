#include "sdl.h"
#include "func.h"
#include <functional>

namespace util
{
namespace sdl
{
SDL_Surface *create(const SDL_Point &size)
{
    if (size.x == 0 || size.y == 0)
        throw std::invalid_argument("Invalid size argument for create");
    auto res =
        SDL_CreateRGBSurface(0, size.x, size.y, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    SDL_FillRect(res, NULL, 0);
    return res;
}

void destroy(SDL_Surface *surface)
{
    if (surface != nullptr) delete surface;
}

void copyTo(SDL_Surface *src, SDL_Surface *dst) { blit(src, NULL, dst, NULL); }

SDL_Surface *copy(SDL_Surface *src)
{
    auto dst = create({src->w, src->h});
    blit(src, NULL, dst, NULL);
    return dst;
}

void blit(SDL_Surface *src, const SDL_Rect *src_r, SDL_Surface *dst,
          const SDL_Rect *dst_r)
{
    if (dst_r)
    {
        SDL_Rect _dst_r{*dst_r};
        SDL_BlitSurface(src, src_r, dst, &_dst_r);
    }
    else
    {
        SDL_BlitSurface(src, src_r, dst, NULL);
    }
}

SDL_Surface *patch(SDL_Surface *src, const SDL_Rect &rect)
{
    auto dst = create(SDL_Point{rect.w, rect.h});
    blit(src, &rect, dst, NULL);
    return dst;
}

Uint32 getPixel(const SDL_Surface *_surface, int x, int y)
{
    int bpp = _surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)_surface->pixels + y * _surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0; /* shouldn't happen, but avoids warnings */
    }
}

void setPixel(SDL_Surface *_surface, int x, int y, Uint32 pixel)
{
    int bpp = _surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)_surface->pixels + y * _surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

Uint32 color2uint(const SDL_Surface *surface, const SDL_Color &c)
{
    Uint32 u_color;
    auto get_shift_size = [](Uint32 mask) -> unsigned int {
        for (int i = 0; i < 32; i++)
            if (mask & 1 << i) return i;
        throw "Invalid pixel mask";
    };

    const SDL_PixelFormat &fmt = *(surface->format);
    u_color |= c.a << get_shift_size(fmt.Amask);
    u_color |= c.r << get_shift_size(fmt.Rmask);
    u_color |= c.g << get_shift_size(fmt.Gmask);
    u_color |= c.b << get_shift_size(fmt.Bmask);
    return u_color;
}

SDL_Color uint2color(const SDL_Surface *surface, const Uint32 &c)
{
    const SDL_PixelFormat &fmt = *(surface->format);
    SDL_Color color;
    color.a = fmt.Amask & c;
    color.r = fmt.Rmask & c;
    color.g = fmt.Gmask & c;
    color.b = fmt.Bmask & c;
    return color;
}

void fillColor(SDL_Surface *surface, const SDL_Color &c)
{
    const SDL_PixelFormat &fmt = *(surface->format);
    auto u_color = color2uint(surface, c);

    for (int x = 0; x < surface->w; x++)
        for (int y = 0; y < surface->h; y++)
            if (getPixel(surface, x, y) & fmt.Amask)
                setPixel(surface, x, y, u_color);
}

bool cmpColor(const SDL_Color &a, const SDL_Color &b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

bool cmpRect(const SDL_Rect &a, const SDL_Rect &b)
{
    return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h;
}
bool cmpPos(const SDL_Point &a, const SDL_Point &b)
{
    return a.x == b.x && a.y == b.y;
}

SDL_Rect getTightRect(const SDL_Surface *surface)
{
    using check_func = std::function<bool(const SDL_Surface *, const int)>;

    auto check_row = [](const SDL_Surface *surface, const int y) -> bool {
        for (int x = 0; x < surface->w; x++)
            if (getPixel(surface, x, y) != 0) return true;
        return false;
    };
    auto check_col = [](const SDL_Surface *surface, const int x) -> bool {
        for (int y = 0; y < surface->h; y++)
            if (getPixel(surface, x, y) != 0) return true;
        return false;
    };
    auto find_var = [&surface](check_func func, unsigned int max,
                               bool reversed = false) -> int {
        auto range = util::range<unsigned int>(0, max);
        if (reversed) std::reverse(range.begin(), range.end());

        for (auto i : range)
            if (func(surface, i)) return static_cast<int>(i);

        throw std::invalid_argument("Cannot find var in range");
    };

    auto min_x = find_var(check_col, surface->w);
    auto max_x = find_var(check_col, surface->w, true);
    auto min_y = find_var(check_row, surface->h);
    auto max_y = find_var(check_row, surface->h, true);

    return SDL_Rect{min_x, min_y, max_x - min_x + 1, max_y - min_y + 1};
}

SDL_Surface *rotate(SDL_Surface *surf, FlipStatus flip)
{
    if (flip.vertical == flip.horizontal && flip.vertical == false)
        return copy(surf);

    auto temp = create({surf->w, surf->h});

    for (int x = 0, rx = temp->w - 1; x < temp->w; x++, rx--)
    {
        for (int y = 0, ry = temp->h - 1; y < temp->h; y++, ry--)
        {
            auto pixel = getPixel(surf, x, y);
            auto tx = flip.horizontal ? ry : y;
            auto ty = flip.vertical ? rx : x;

            setPixel(temp, tx, ty, pixel);
        }
    }
    return temp;
}

std::set<SDL_Point> boundary(const SDL_Surface *surface)
{
    auto is_valid = [](const SDL_Surface *surface, SDL_Point p) -> bool {
        return util::sdl::getPixel(surface, p.x, p.y) != 0;
    };

    auto check_row = [&](const std::vector<int> &range, const int y) -> int {
        for (auto x : range)
            if (is_valid(surface, {x, y})) return x;
        return -1;
    };
    auto check_col = [&](const std::vector<int> &range, const int x) -> int {
        for (auto y : range)
            if (is_valid(surface, {x, y})) return y;
        return -1;
    };

    auto cols = util::range(0, surface->w);
    auto r_cols = util::func::reverse(cols);
    auto rows = util::range(0, surface->h);
    auto r_rows = util::func::reverse(rows);
    std::set<SDL_Point> target;
    for (auto _rows : {rows, r_rows})
        for (auto col : cols)
            target.insert(SDL_Point{col, check_col(_rows, col)});

    for (auto _cols : {cols, r_cols})
        for (auto row : rows)
            target.insert(SDL_Point{row, check_row(_cols, row)});

    return target;
}

}; // namespace sdl

}; // namespace util
