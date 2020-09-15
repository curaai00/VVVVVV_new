#include "../src/BlockV.h"
#include "../src/Finalclass.h"
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
    // expect_eq()
}

TEST(TestJSON, load_finalevel)
{
    short contents[1200] = { 0 };
    char* assetsPath = "/Users/jeongpilseong/workspace/proj/VVVVVV/"
                       "desktop_version/data";
    // "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\Debug\\data";
    char* argvZero =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/VVVVVV_run";
    // "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\Debug\\data";
    FILESYSTEM_init(argvZero, argvZero, assetsPath);

    auto parse_json = [](const char* path) -> nlohmann::json {
        unsigned char* uMem = NULL;
        FILESYSTEM_loadFileToMemory(path, &uMem, NULL, true);
        return nlohmann::json::parse(uMem);
    };
    auto load_content_arr = [&contents](const nlohmann::json& _jsonarr) {
        for (int i = 0; i < 1200; i++)
            contents[i] = _jsonarr[i].get<short>();
    };

    auto level_table = parse_json("final_level.json");
    auto sample = level_table["5250"];
    auto _json = sample["entities"][0];
    load_content_arr(sample["content"]);
    //             { "xp": 163,"yp": 32,"t": 12,"vx": 168 },

    float xp, yp, vx, vy = 0;
    int t, p1, p2, p3, p4 = 0;
    if (_json.contains("xp"))
        xp = _json["xp"].get<float>();
    if (_json.contains("yp"))
        yp = _json["yp"].get<float>();
    if (_json.contains("t"))
        t = _json["t"].get<int>();
    if (_json.contains("vx"))
        vx = _json["vx"].get<float>();

    EXPECT_FLOAT_EQ(163, xp);
    EXPECT_FLOAT_EQ(32, yp);
    EXPECT_FLOAT_EQ(12, t);
    EXPECT_FLOAT_EQ(168, vx);

    EXPECT_EQ(contents[0], 98);
}