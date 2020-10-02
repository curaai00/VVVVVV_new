#include "Background.h"

Background::Background()
    : Layer()
{
    auto res = towerdata.asset.count("background");
    tower = towerdata.asset["background"].get<std::vector<unsigned short>>();
}
Background::~Background() {}

void Background::draw(void)
{
    SDL_FillRect(_surface, NULL, 0x00000000);

    for (int y = 0; y < 30; y++) {
        for (int x = 0; x < 40; x++) {
            auto yoff = (_scroll_start_y + y) % 120;
            auto var = tower[yoff * 40 + x];
            SDL_Rect rect{ x * 8, y * 8, 8, 8 };
            SDL_BlitSurface(
                colortile.getTile(var + _color * 30), NULL, _surface, &rect);
        }
    }
}

void Background::scroll(void)
{
    ++_scroll_start_y %= 120;
}

unsigned int Background::getColor(void) const
{
    return _color;
}

void Background::setColor(void)
{
    ++_color %= 30;
}

void Background::setColor(unsigned int c)
{
    if (0 <= c && c < 30)
        _color = c;
    else
        throw std::out_of_range("This Color out of tile colorspace");
}