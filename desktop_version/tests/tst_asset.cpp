#include "../new/Resource.h"
#include "../new/util.h"
#include "gtest/gtest.h"

TEST(TestAsset, JSON)
{
    JsonAsset _json("tower.json");
    auto exists = [&](const char* k) -> bool {
        return _json.asset.find(k) != _json.asset.end();
    };

    EXPECT_TRUE(exists("minitower1"));
    EXPECT_TRUE(exists("minitower2"));
    EXPECT_TRUE(exists("background"));
    EXPECT_TRUE(exists("map"));
}

TEST(TestAsset, temp)
{
    auto get_shift_size = [](Uint32 mask) -> unsigned int {
        for (int i = 0; i < 32; i++)
            if (mask & 1 << i)
                return i;
        throw "Invalid pixel mask";
    };

    EXPECT_EQ(get_shift_size(R_MASK), 0);
    EXPECT_EQ(get_shift_size(G_MASK), 8);
    EXPECT_EQ(get_shift_size(B_MASK), 16);
    EXPECT_EQ(get_shift_size(A_MASK), 24);
}