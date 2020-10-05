#include "../new/Map.h"
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
    EXPECT_STREQ(room->name(), "Conundrum");
    EXPECT_EQ(room->blockCount(), 2);
}
TEST_F(TestRoom, blocks)
{
    auto blocks = room->blocks();
    EXPECT_EQ(blocks[0]->getDrawRect(), SDL_Rect(0, 0, 320, 240));
    EXPECT_EQ(blocks[0]->tileCount(), 1234);
    // something small spikes
    EXPECT_EQ(blocks[1]->getDrawRect(), SDL_Rect(1, 2, 3, 4));
    EXPECT_EQ(blocks[1]->tileCount(), 10);
}