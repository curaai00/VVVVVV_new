#include "../new/Message.h"
#include "../new/util.h"
#include "gtest/gtest.h"

#include <exception>
#include <iostream>

class TestMessage : public ::testing::Test
{
public:
    TestMessage() {}

protected:
    Message msg{ SDL_Point{ 0, 0 }, SDL_Color{ 255, 255, 255, 255 }, "VVVVVV" };
};

TEST_F(TestMessage, drawMessage)
{
    auto surface = util::sdl::CreateSurface({320, 240});
    auto msg_rect = msg.rect();
    SDL_BlitSurface(msg.surface(), NULL, surface, &msg_rect);


    Uint32 a = util::sdl::ReadPixel(msg.surface(), 0, 0);
    Uint32 c = util::sdl::ReadPixel(surface, 0, 0);
    auto temp = util::sdl::uint2color(surface, c);
    EXPECT_EQ(c, 0xFFFFFFFF);
    EXPECT_EQ(c, a);
    a = util::sdl::ReadPixel(msg.surface(), 0, 8);
    c = util::sdl::ReadPixel(surface, 0, 8);
    EXPECT_EQ(c, 0x00000000);
    EXPECT_EQ(c, a);

    auto rect = msg.rect();
    EXPECT_EQ(rect.x, 0);
    EXPECT_EQ(rect.y, 0);
    EXPECT_EQ(rect.w, 48);
    EXPECT_EQ(rect.h, 8);

    delete surface;
}