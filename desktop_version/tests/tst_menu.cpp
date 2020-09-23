#include "../src/Game.h"
#include "../src/Graphics.h"

#include "gtest/gtest.h"

class TestMenu : public ::testing::Test
{
public:
    TestMenu()
    {
        g.createmenu(Menu::mainmenu);
        g.menu_.setCurOptIdx(2);
    }

protected:
    Game g;
    Graphics graphics;
};

TEST_F(TestMenu, OpenGraphicoptions)
{
    g.createmenu(Menu::graphicoptions);

    auto board = g.menu_.getCurBoard();

    EXPECT_EQ(board.cur_option_name, Menu::graphicoptions);
    EXPECT_EQ(board.xoff, 37);
    EXPECT_EQ(board.yoff, -10);
    EXPECT_EQ(board.spacing, 25);
    EXPECT_EQ(board.options.size(), 8);
    EXPECT_EQ(true, true);
}

TEST_F(TestMenu, GoAndBack)
{
    auto before = g.menu_.getCurBoard();

    g.createmenu(Menu::graphicoptions);
    g.menu_.back();

    auto after = g.menu_.getCurBoard();

    EXPECT_EQ(before.xoff, after.xoff);
    EXPECT_EQ(before.yoff, after.yoff);
    EXPECT_EQ(before.cur_option_name, after.cur_option_name);
    EXPECT_EQ(before.cur_option_idx, after.cur_option_idx);
    EXPECT_EQ(before.options.size(), after.options.size());
}