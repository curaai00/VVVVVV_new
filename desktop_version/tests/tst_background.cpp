#include "../new/Background.h"
#include "gtest/gtest.h"
#include <exception>
#include <iostream>

// class TestBackground : public ::testing:Test
// {
//     protected:

// };

TEST(TestBackground, makeTiles)
{
    PNGAsset colortile{ "graphics/tiles3.png" };

    EXPECT_EQ(colortile.asset->h / 8, 30);
    EXPECT_EQ(colortile.asset->w / 8, 30);

    // throw std::invalid_argument("asdf");

    std::vector<SDL_Surface*> tiles;
    for (int j = 0; j < colortile.asset->h / 8; j++)
        for (int i = 0; i < colortile.asset->w / 8; i++) {
            tiles.push_back(
                GetSubSurface(colortile.asset, SDL_Rect{ i * 8, j * 8, 8, 8 }));
        }

    EXPECT_EQ(tiles.size(), 900);
}