#include "../new/Sprite.h"
#include "../new/util.h"
#include "gtest/gtest.h"

#include <exception>
#include <iostream>

class TestSprite : public ::testing::Test
{
public:
    TestSprite() {}

protected:
    Sprite sprite{ SDL_Point{ 0, 0 }, 23 };
};

TEST_F(TestSprite, loadSimpleV)
{
    auto surface = sprite.surface();
    auto pix1 = util::sdl::ReadPixel(surface, 0, 0);
    auto pix2 = util::sdl::ReadPixel(surface, 4, 8);
    EXPECT_EQ(pix1, 0x00000000);
    EXPECT_EQ(pix2, 0xFF01A4D9);
}
