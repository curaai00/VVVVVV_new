#include "Message.h"
#include "util.h"

Message::Message(SDL_Point xy, SDL_Color color, std::string msg)
    : ObjectDrawable()
    , xy(xy)
    , color(color)
    , msg(msg)
{
    int idx;
    int curr;
    int bfontpos = 0;

    // need for global rect of drawable
    auto temp_surface =
        SDL_CreateRGBSurface(0, 320, 240, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    SDL_FillRect(temp_surface, NULL, 0x00000000);
    bool first = true;
    SDL_Rect font_rect;

    auto iter = msg.begin();
    while (iter != msg.end()) {
        curr = utf8::unchecked::next(iter);
        font_rect = tfont_rect;
        font_rect.x = xy.x + bfontpos;
        font_rect.y = xy.y;

        if (first) {
            _draw_rect.x = font_rect.x;
            _draw_rect.y = font_rect.y;
            first = false;
        }

        SDL_BlitSurface(
            font_tile.getTile(curr), NULL, temp_surface, &font_rect);
        bfontpos += curr < 32 ? 6 : 8;
    }
    _draw_rect.w = font_rect.x - _draw_rect.x + font_rect.w;
    _draw_rect.h = font_rect.h;

    _surface = SDL_CreateRGBSurface(
        0, _draw_rect.w, _draw_rect.h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    SDL_BlitSurface(temp_surface, &_draw_rect, _surface, NULL);
    SDL_FreeSurface(temp_surface);
}