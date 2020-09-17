#include "Spacestation2.h"

#include "Entity.h"
#include "Game.h"
#include "MakeAndPlay.h"
#include "UtilityClass.h"

spacestation2class::spacestation2class()
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
    station_table = parse_json("spacestation.json");
}

// clang--format off
const short* spacestation2class::loadlevel(int rx, int ry)
{
    int t;
    rx -= 100;
    ry -= 100;

    rx += 50 - 12;
    ry += 50 - 14; // Space Station

    t = rx + (ry * 100);

    const short* result;
    short contents[1200] = { 0 };

    roomname =
        "Untitled room [" + help.String(rx) + "," + help.String(ry) + "]";
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

    const static int key_list[]{
        rn(50, 50), rn(49, 50), rn(49, 49), rn(49, 48), rn(49, 47), rn(50, 47),
        rn(50, 48), rn(50, 49), rn(51, 49), rn(52, 49), rn(53, 49), rn(54, 49),
        rn(54, 48), rn(53, 48), rn(52, 48), rn(51, 48), rn(51, 47), rn(52, 47),
        rn(51, 46), rn(51, 45), rn(51, 44), rn(52, 45), rn(52, 44), rn(53, 45),
        rn(53, 47), rn(53, 46), rn(52, 46), rn(53, 44), rn(54, 45), rn(54, 44),
        rn(54, 47), rn(54, 46), rn(55, 47), rn(55, 46), rn(55, 45), rn(55, 44),
        rn(56, 44), rn(56, 45), rn(56, 46), rn(56, 47), rn(56, 48), rn(56, 49),
        rn(56, 50), rn(53, 43), rn(56, 43), rn(55, 43), rn(54, 43), rn(52, 43),
        rn(51, 43), rn(50, 43), rn(49, 43), rn(48, 43), rn(48, 42), rn(49, 42),
        rn(49, 41), rn(48, 41), rn(53, 42), rn(54, 42), rn(52, 42), rn(50, 42),
        rn(51, 42), rn(50, 41), rn(50, 40), rn(51, 40), rn(50, 39), rn(51, 39),
        rn(52, 39), rn(53, 39), rn(53, 40), rn(53, 41), rn(52, 41), rn(51, 41),
        rn(52, 40)

    };
    auto key = std::to_string(t);
    if (station_table.contains(key)) {
        auto cur_level = station_table[key];
        roomname = cur_level["roomname"].get<std::string>();

        for (const auto& entity : cur_level["entities"])
            create_entity(entity);

        load_content_arr(cur_level["content"]);

        switch (t) {
#if !defined(MAKEANDPLAY)
            case rn(50, 50):
                if (game.intimetrial)
                    obj.createentity(
                        136, 92, 11, 48); // (horizontal gravity line)
                break;
            case rn(50, 48):
                obj.platformtile = 119;
                break;
            case rn(54, 49):
                obj.platformtile = 319;
                break;
            case rn(54, 48):
                obj.platformtile = 10;
                break;
            case rn(53, 48):
                obj.platformtile = 279;
                break;
            case rn(52, 48):
                obj.platformtile = 359;
                break;
            case rn(51, 44):
                if (!game.intimetrial)
                    obj.createentity(18 * 8, 5 * 8 + 4, 14);
                break;
            case rn(52, 44):
                obj.createblock(5, 124 - 4, 120, 20, 16, 14);
                obj.createblock(5, 156 - 4, 40, 20, 16, 15);
                break;
            case rn(55, 45):
                obj.platformtile = 159;
                break;
            case rn(56, 50):
                obj.createblock(5, 24 - 4, 152, 20, 16, 16);
                break;
            case rn(53, 43):
                obj.platformtile = 707;
                if (game.intimetrial && game.timetriallevel > 0)
                    obj.fatal_top();
                break;
            case rn(56, 43):
                if (game.intimetrial) {
                    obj.createblock(1, 56 + 16, 0, 32, 150, 82);
                } else {
                    if (!obj.flags[7]) {
                        if (game.nocutscenes) {
                            obj.flags[7] = true;
                            game.teleportscript = "levelonecomplete";
                        } else {
                            obj.createblock(1, 56, 0, 32, 150, 32);
                        }
                    }
                }
                break;
            case rn(50, 43):
                if (!game.nocutscenes)
                    obj.createblock(1, 0, 0, 112, 112, 8);
                break;
            case rn(49, 43): {
                int spikevalue = (game.nodeathmode || game.intimetrial) ? 0 : 9;
                for (int i = 23; i < 23 + 14; i++)
                    contents[i + 8 * 40] = spikevalue;
                obj.platformtile = 747;
                if (game.nodeathmode)
                    roomname = "I Can't Believe You Got This Far";
                else if (game.intimetrial)
                    roomname = "Imagine Spikes There, if You Like";
                break;
            }
            case rn(48, 42):
                obj.platformtile = 239;
                break;
            case rn(49, 41):
                if (!game.intimetrial) {
                    if (game.companion == 0 && !obj.flags[10] &&
                        !game.crewstats[2]) // also need to check if he's
                    {
                        obj.createentity(42, 86, 16, 0);
                        obj.createblock(1, 0, 0, 140, 240, 34);
                    }
                }
                break;
            case rn(48, 41):
                if (game.intimetrial)
                    obj.createblock(1, 280, 0, 32, 240, 82);
                break;
            case rn(54, 42):
                if (!game.nocutscenes) {
                    if (!obj.flags[68]) {
                        obj.createblock(1, 32, 0, 320, 240, 17);
                        obj.flags[68] = true;
                    }
                }
                break;
            case rn(51, 42):
                obj.platformtile = 207;
                if (!game.nocutscenes)
                    obj.createblock(1, 16, 0, 320, 240, 47);
                break;
            case rn(50, 40):
                obj.platformtile = 10;
                break;
            case rn(51, 40):
                if (!game.intimetrial)
                    obj.createblock(1, 120, 0, 320, 240, 31);
                break;
            case rn(51, 39):
                obj.createblock(5, 256 - 8, 200, 20, 16, 6);
                break;
            case rn(53, 41):
                if (!game.nocutscenes)
                    obj.createblock(1, 72, 0, 320, 240, 30);
                break;
            case rn(52, 41):
                if (!game.nocutscenes) {
                    obj.createblock(1, 10, 0, 60, 240, 22);
                    obj.createblock(1, 280, 0, 320, 240, 21);
                }
                break;
        };
#endif

    } else {
        obj.fatal_bottom();
    }
    result = contents;
    return result;
}

// clang--format on
