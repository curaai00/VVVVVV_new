#include "WarpClass.h"

#include "Entity.h"
#include "Game.h"
#include "MakeAndPlay.h"
#include "UtilityClass.h"

warpclass::warpclass()
{
    auto parse_json = [](const char* path) -> nlohmann::json {
        unsigned char* uMem = NULL;
        FILESYSTEM_loadFileToMemory(path, &uMem, NULL, true);
        return nlohmann::json::parse(uMem);
    };

    char* assetsPath =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/data";
    // "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\Debug\\data";
    char* argvZero =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/VVVVVV_run";
    // "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\Debug\\data";
    FILESYSTEM_init(argvZero, argvZero, assetsPath);
    warp_table = parse_json("script.json");
}

const short* warpclass::loadlevel(int rx, int ry)
{
    int t;

    rx -= 100;
    ry -= 100;
    rx += 50 - 14;
    ry += 49; // warp

    t = rx + (ry * 100);
    rcol = 0;
    warpx = false;
    warpy = false;
    short contents[1200] = { 0 };

    roomname =
        "Untitled room [" + help.String(rx) + "," + help.String(ry) + "]";
    const static int key_list[]{ rn(50, 50), rn(51, 50), rn(51, 51), rn(52, 51),
                                 rn(52, 50), rn(53, 50), rn(53, 49), rn(54, 49),
                                 rn(54, 50), rn(55, 50), rn(55, 51), rn(54, 51),
                                 rn(54, 52), rn(53, 52), rn(53, 51), rn(55, 49),
                                 rn(55, 52), rn(52, 52), rn(50, 51), rn(52, 49),
                                 rn(50, 49), rn(51, 49), rn(49, 49) };

    auto create_entity = [&](const nlohmann::json& _json) {
        float xp(0), yp(0), vx(0), vy(0);
        int t(0), p1(0), p2(0), p3(0), p4(0);

        if (_json.contains("xp"))
            xp = _json["xp"].get<float>();
        if (_json.contains("yp"))
            yp = _json["yp"].get<float>();
        if (_json.contains("t"))
            t = _json["t"].get<int>();
        if (_json.contains("vx"))
            vx = _json["vx"].get<float>();
        if (_json.contains("vy"))
            vy = _json["vy"].get<float>();
        if (_json.contains("p1"))
            p1 = _json["p1"].get<int>();
        if (_json.contains("p2"))
            p2 = _json["p2"].get<int>();
        if (_json.contains("p3"))
            p3 = _json["p3"].get<int>();
        if (_json.contains("p4"))
            p4 = _json["p4"].get<int>();
        obj.createentity(xp, yp, t, vx, vy, p1, p2, p3, p4);
    };
    auto load_content_arr = [&contents](const nlohmann::json& _jsonarr) {
        for (int i = 0; i < 1200; i++)
            contents[i] = _jsonarr[i].get<short>();
    };

    auto key = std::to_string(t);
    if (warp_table.contains(key)) {
        auto cur_level = warp_table[key];
        roomname = cur_level["roomname"].get<std::string>();

        for (const auto& entity : cur_level["entities"])
            create_entity(entity);

        if (cur_level.contains("rcol"))
            rcol = cur_level["rcol"].get<int>();
        if (cur_level.contains("warpx"))
            warpx = cur_level["warpx"].get<bool>();
        if (cur_level.contains("warpy"))
            warpy = cur_level["warpy"].get<bool>();

        load_content_arr(cur_level["content"]);

        switch (t) {
#if !defined(MAKEANDPLAY)
            case rn(50, 50): {
                if (game.intimetrial) {
                    obj.createblock(0, 0, 0, 8, 240);
                }
                break;
            }

            case rn(54, 50): {

                if (!game.intimetrial) {
                    obj.createentity((7 * 8) + 4, (6 * 8), 14); // Teleporter!
                }
                break;
            }

            case rn(54, 51): {
                obj.createblock(5, 8 - 8, 32, 20, 16, 17);
                break;
            }
            case rn(53, 52): {
                obj.createblock(5, 24 - 8, 200, 20, 16, 18);
                break;
            }
            case rn(51, 49): {
                if (game.intimetrial) {
                    obj.createblock(1, 20, 0, 32, 240, 82);
                }
                break;
            }

            case rn(49, 49): {
                if (!game.intimetrial) {
                    if (game.companion == 0 && !obj.flags[11] &&
                        !game.crewstats[4]) // also need to check if he's
                                            // rescued in a previous game
                    {
                        obj.createentity(255, 121, 15, 0);
                        obj.createblock(1, 215, 0, 160, 240, 35);
                    }
                }
                break;
            }
#endif
        }
    }
    return contents;
}
