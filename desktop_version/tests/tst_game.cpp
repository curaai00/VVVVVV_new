#include "../src/BlockV.h"
#include "../src/Game.h"
#include "gtest/gtest.h"

TEST(TestGame, string2button)
{
    SDL_GameControllerButton exp_btn =
        SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_INVALID;
    auto res = GetButtonFromString("0", &exp_btn);
    EXPECT_TRUE(res);
    EXPECT_EQ(exp_btn, SDL_CONTROLLER_BUTTON_A);
}

TEST(TestBlock, string2color)
{
    blockclass bc;
    bc.setblockcolour("red");
    EXPECT_EQ(bc.r, 255);
    EXPECT_EQ(bc.g, 60);
    EXPECT_EQ(bc.b, 60);
}

TEST(TestMenu, loadTable)
{
    SimpleMenu m;
    bool res = m.hasSimpleDescMsg(Menu::name::options, 0);
    EXPECT_EQ(res, true);
}