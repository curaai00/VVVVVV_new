#include "../src/Game.h"
#include "gtest/gtest.h"

TEST(TestGame, string2button) {
    SDL_GameControllerButton exp_btn = SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_INVALID;
    auto res = GetButtonFromString("0", &exp_btn);
    EXPECT_TRUE(res);
    EXPECT_EQ(exp_btn, SDL_CONTROLLER_BUTTON_A);
}