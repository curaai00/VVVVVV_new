#include "../new/Background.h"
#include "gtest/gtest.h"

#include <exception>
#include <iostream>

class TestBackground : public ::testing::Test
{
public:
    TestBackground() {}

protected:
    IntroBackground back;
};

TEST_F(TestBackground, makeTiles)
{
    EXPECT_EQ(back.colortile.asset->h / 8, 30);
    EXPECT_EQ(back.colortile.asset->w / 8, 30);
    EXPECT_EQ(back.colortile.getTileCount(), 900);
}

TEST_F(TestBackground, spaceEvent)
{
    EXPECT_EQ(back.getColor(), 0);
    back.setColor();
    EXPECT_EQ(back.getColor(), 1);
}