#include "Message.h"
#include "util.h"

Message::Message(SDL_Point xy, SDL_Color color, std::string msg,
                 bool center)
    : Drawable()
    , xy(xy)
    , color(color)
    , msg(msg)
{
    if (center) xy.x = 160 - util::str::len(msg) / 2;

    int bfontpos = 0;

    // need for global rect of drawable
    auto temp_surface = util::sdl::CreateSurface({320, 240});
    SDL_Rect font_rect;

    auto iter = msg.begin();
    while (iter != msg.end())
    {
        auto curr = utf8::unchecked::next(iter);
        font_rect = tfont_rect;
        font_rect.x = xy.x + bfontpos;
        font_rect.y = xy.y;

        SDL_BlitSurface(font_tile.tile(curr), NULL, temp_surface,
                        &font_rect);
        bfontpos += curr < 32 ? 6 : 8;
    }

    _draw_rect.x = xy.x;
    _draw_rect.y = xy.y;
    _draw_rect.w = font_rect.x - _draw_rect.x + font_rect.w;
    _draw_rect.h = font_rect.h;

    _surface = util::sdl::CreateSurface({_draw_rect.w, _draw_rect.h});

    SDL_BlitSurface(temp_surface, &_draw_rect, _surface, NULL);
    SDL_FreeSurface(temp_surface);

    _color = new ColorComponent(color);
    _color->paint(_surface);
}

Message::~Message() { delete _color; }
