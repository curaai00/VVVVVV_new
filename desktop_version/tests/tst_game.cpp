#include "../src/Game.h"
#include "gtest/gtest.h"

// class TestGame : public ::testing::Test
// {
// public:
//     TestGame()
//         : Test()
//     {
//     }

// protected:
//     virtual void SetUp()
//     {
//     }

// };

// TEST_F(TestGame, string2button) {
//     SDL_GameControllerButton exp_btn;
//     auto res = GetButtonFromString("0", &exp_btn);
//     EXPECT_EQ(exp_btn, SDL_CONTROLLER_BUTTON_A);
//     EXPECT_EQ(1, 1);
// }


TEST(TestGame, string2button) {
    SDL_GameControllerButton exp_btn;
    auto res = GetButtonFromString("0", &exp_btn);
    EXPECT_EQ(exp_btn, SDL_CONTROLLER_BUTTON_A);
    EXPECT_EQ(1, 1);
}