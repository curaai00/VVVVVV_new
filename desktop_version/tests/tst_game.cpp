#include "../new/Game.h"
#include "gtest/gtest.h"

#include <exception>
#include <iostream>

using namespace util::sdl;

class TestGame : public ::testing::Test
{
protected:
    virtual void SetUp() { game = new Game(); }

protected:
    Game *game;
};

TEST_F(TestGame, move_character)
{
    auto character = static_cast<Character *>(game->EventEntities::elements()[0]);
    auto &pos = character->drawable();
    SDL_Rect expect_rect{290, 162, 10, 21};
    EXPECT_EQ(pos.rect.x, expect_rect.x);
    EXPECT_EQ(pos.rect.y, expect_rect.y);
    EXPECT_EQ(pos.rect.w, expect_rect.w);
    EXPECT_EQ(pos.rect.h, expect_rect.h);

    auto move = static_cast<MoveEvent *>(character->EventEntity::elements()[0]);
    move->move(EMove::LEFT);

    EXPECT_EQ(pos.rect.x, expect_rect.x - 1);
}

TEST_F(TestGame, flip_character)
{
    auto character = static_cast<Character *>(game->EventEntities::elements()[0]);
    auto &pos = character->drawable();
    SDL_Rect expect_rect{290, 162, 10, 21};
    EXPECT_EQ(pos.rect.x, expect_rect.x);
    EXPECT_EQ(pos.rect.y, expect_rect.y);
    EXPECT_EQ(pos.rect.w, expect_rect.w);
    EXPECT_EQ(pos.rect.h, expect_rect.h);

    auto gravity =
        static_cast<GravityEvent *>(character->EventEntity::elements()[1]);
    gravity->update(SDLK_SPACE);
    character->DrawableEntity::update();

    EXPECT_EQ(pos.rect.y, expect_rect.y - 1);
}