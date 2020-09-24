#include "Background.h"

Background::Background()
{
    // tower =
    //     towerdata.asset["background"].get<std::array<unsigned short,
    //     4800>>();
    auto res = towerdata.asset.count("background");
    tower = towerdata.asset["background"].get<std::vector<unsigned short>>();

    for (int j = 0; j < colortile.asset->h / 8; j++)
        for (int i = 0; i < colortile.asset->w / 8; i++)
            tiles.push_back(GetSubSurface(colortile.asset, i * 8, j * 8, 8, 8));

    for (int r = 0; r < 32; r++) {
        for (int c = 0; c < 40; c++) {
            auto x = tower[c * 8 + r];

            SDL_Rect rect{ c, r, 8, 8 };
            SDL_BlitSurface(tiles[x], NULL, surface, &rect);
        }
    }
}

void Background::draw(void)
{
    // for (int r = 0; r < 32; r++) {
    //     for (int c = 0; c < 40; c++) {
    //         auto x = tower[c * 8 + r];
    //         SDL_Rect r{ c, r, 8, 8 };
    //         SDL_BlitSurface(tiles[x], NULL, surface, r);
    //     }
    // }
}