#include "../new/Resource.h"
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