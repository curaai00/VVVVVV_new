#include "Background.h"

Background::Background()
{
    surface = SDL_CreateRGBSurface(
        0, 320, 240, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    auto res = towerdata.asset.count("background");
    tower = towerdata.asset["background"].get<std::vector<unsigned short>>();

    for (int j = 0; j < colortile.asset->h / 8; j++)
        for (int i = 0; i < colortile.asset->w / 8; i++)
            tiles.push_back(
                GetSubSurface(colortile.asset, SDL_Rect{ i * 8, j * 8, 8, 8 }));
}

void Background::draw(void)
{
    for (int y = 0; y < 30; y++) {
        for (int x = 0; x < 40; x++) {
            auto yoff = (scroll_start_y + y) % 120;
            auto var = tower[yoff * 40 + x];

            SDL_Rect rect{ x * 8, y * 8, 8, 8 };
            SDL_BlitSurface(tiles[var], NULL, surface, &rect);
        }
    }
}

void Background::scroll(void)
{
    ++scroll_start_y %= 120;
}