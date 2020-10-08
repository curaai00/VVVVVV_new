#include "../new/Background.h"
#include "../new/util.h"
#include "gtest/gtest.h"

#include <exception>
#include <iostream>

using namespace util::sdl;

class TestIntroBackground : public ::testing::Test
{
protected:
    virtual void SetUp() { back = new IntroBackground(); }
    virtual void TearDown() { delete back; }

protected:
    IntroBackground* back;
};

TEST_F(TestIntroBackground, color)
{
    auto _surface = back.surface();
    auto res_c = uint2color(ReadPixel(_surface, 0, 0));
    // change after
    auto expect_c = color2uint(0);
    EXPECT_EQ(res_c, expect_c);

    back.stripe.setColor();
    res_c = uint2color(ReadPixel(_surface, 0, 0));
    // change after
    expect_c = color2uint(0);
    EXPECT_EQ(res_c, expect_c);
}

TEST_F(TestIntroBackground, scroll)
{
    back.update();

    auto res_c = uint2color(ReadPixel(_surface, 0, 0));
    // change after
    auto expect_c = color2uint(0);
    EXPECT_EQ(res_c, expect_c);
}
