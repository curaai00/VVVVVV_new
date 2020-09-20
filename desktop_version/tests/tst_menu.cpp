#include "../src/Game.h"
#include "../src/Graphics.h"

#include "gtest/gtest.h"

TEST(TestMenu, OpenAccessibility)

{
    Game g;
    Graphics graphics;

    g.createmenu(Menu::mainmenu);
    g.createmenu(Menu::graphicoptions);

    auto board = g.menu_.getCurBoard();

    EXPECT_EQ(board.cur_option_name, Menu::graphicoptions);
    EXPECT_EQ(board.xoff, 37);
    EXPECT_EQ(board.yoff, -10);
    EXPECT_EQ(board.spacing, 25);
    EXPECT_EQ(board.options.size(), 8);
    EXPECT_EQ(true, true);
}