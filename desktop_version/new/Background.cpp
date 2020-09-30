#include "Background.h"

Background::Background()
{
    surface = SDL_CreateRGBSurface(
        0, 320, 240, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    auto res = towerdata.asset.count("background");
    tower = towerdata.asset["background"].get<std::vector<unsigned short>>();

    for (int j = 0; j < colortile.asset->h; j += 8) {
        for (int i = 0; i < colortile.asset->w; i += 8) {
            auto tile = GetSubSurface(colortile.asset, SDL_Rect{ i, j, 8, 8 });
            // SDL_LockSurface(tile);
            tiles.push_back(tile);
        }
    }
}
Background::~Background()
{
    if (surface)
        SDL_FreeSurface(surface);
    for (auto tile : tiles)
        if (tile)
            SDL_FreeSurface(tile);
}

void Background::draw(void)
{
    SDL_UnlockSurface(surface);

    for (int y = 0; y < 30; y++) {
        for (int x = 0; x < 40; x++) {
            auto yoff = (_scroll_start_y + y) % 120;
            auto var = tower[yoff * 40 + x];

            SDL_Rect rect{ x * 8, y * 8, 8, 8 };
            SDL_BlitSurface(tiles[var + _color * 30], NULL, surface, &rect);
        }
    }

    SDL_LockSurface(surface);
}

void Background::scroll(void)
{
    ++_scroll_start_y %= 120;
}

bool Background::event(const SDL_Keycode k)
{
    switch (k) {
        case SDLK_SPACE:
            setColor();
            break;
        default:
            return false;
    }
    return true;
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