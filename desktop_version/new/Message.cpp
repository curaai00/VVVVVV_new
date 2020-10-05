#include "Message.h"
#include "util.h"

Message::Message(SDL_Point xy, SDL_Color color, std::string msg, bool center)
    : Drawable()
    , xy(xy)
    , color(color)
    , msg(msg)
{
    if (center)
        xy.x = 160 - util::str::len(msg) / 2;

    int bfontpos = 0;

    // need for global rect of drawable
    auto temp_surface =
        SDL_CreateRGBSurface(0, 320, 240, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    SDL_FillRect(temp_surface, NULL, 0x00000000);
    SDL_Rect font_rect;

    auto iter = msg.begin();
    while (iter != msg.end()) {
        auto curr = utf8::unchecked::next(iter);
        font_rect = tfont_rect;
        font_rect.x = xy.x + bfontpos;
        font_rect.y = xy.y;

        SDL_BlitSurface(
            font_tile.getTile(curr), NULL, temp_surface, &font_rect);
        bfontpos += curr < 32 ? 6 : 8;
    }

    _draw_rect.x = xy.x;
    _draw_rect.y = xy.y;
    _draw_rect.w = font_rect.x - _draw_rect.x + font_rect.w;
    _draw_rect.h = font_rect.h;

    _surface = SDL_CreateRGBSurface(
        0, _draw_rect.w, _draw_rect.h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    SDL_BlitSurface(temp_surface, &_draw_rect, _surface, NULL);
    util::sdl::BlitSurfaceColoured(_surface, color);
    _prev_color = color;

    SDL_FreeSurface(temp_surface);
}

void Message::draw(void)
{
    if (util::sdl::cmpColor(_prev_color, color)) {
        util::sdl::BlitSurfaceColoured(_surface, color);
    }
    _prev_color = color;
}

void Message::update(void)
{
    return;
}