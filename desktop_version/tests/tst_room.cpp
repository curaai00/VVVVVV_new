#include "../new/Room.h"
#include "../new/util.h"
#include "gtest/gtest.h"

class TestRoom : public ::testing::Test
{
public:
    TestRoom() { room = new Room{ room_table, map_tile, room_pos }; }

protected:
    Room* room;
    SDL_Point room_pos{ 114, 105 };
    TileAsset map_tile{ "graphics/tiles.png", SDL_Point{ 8, 8 } };
    JsonAsset room_table{ "spacestation.json" };
};

TEST_F(TestRoom, load)
{
    EXPECT_STREQ(room->name().c_str(), "Conundrum");
    EXPECT_EQ(room->blockCount(), 3);
}
TEST_F(TestRoom, blocks)
{
    room->draw();

    SDL_Rect rect;
    // empty 414
    auto blocks = room->blocks();
    rect = SDL_Rect{ 0, 0, 320, 240 };
    EXPECT_TRUE(util::sdl::cmpRect(blocks[0]->rect(), rect));
    EXPECT_EQ(blocks[0]->tileCount(), 772);

    // something small spikes
    EXPECT_EQ(blocks[1]->tileCount(), 14);
    rect = SDL_Rect{ 104, 192, 112, 8 };
    EXPECT_TRUE(util::sdl::cmpRect(blocks[1]->rect(), rect));

    EXPECT_EQ(blocks[2]->tileCount(), 414);
    rect = SDL_Rect{ 0, 104, 320, 88 };
    EXPECT_TRUE(util::sdl::cmpRect(blocks[2]->rect(), rect));
}