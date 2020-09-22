#include "Labclass.h"

#include "Entity.h"
#include "FileSystemUtils.h"
#include "Game.h"
#include "MakeAndPlay.h"
#include "UtilityClass.h"

labclass::labclass()
{
    // TODO replace init to another
    // char* assetsPath = NULL;
    auto parse_json = [](const char* path) -> nlohmann::json {
        unsigned char* uMem = NULL;
        FILESYSTEM_loadFileToMemory(path, &uMem, NULL, true);
        return nlohmann::json::parse(uMem);
    };

#ifdef __WIN32__
    char* assetsPath =
        "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\data";
    char* argvZero =
        "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\data";
#else
    char* assetsPath =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/data";
    char* argvZero =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/VVVVVV_run";
#endif
    FILESYSTEM_init(argvZero, argvZero, assetsPath);
    level_table = parse_json("lab_level.json");
}

labclass::~labclass() {}

const short* labclass::loadlevel(int rx, int ry)
{
    int t;

    rx = rx - 100;
    ry = ry - 100;
    if (ry < 5) {
        rx += 50 - 2;
        ry += 54; // lab
    } else {
        rx += 50 - 2;
        ry += 50 - 16; // lab
    }

    t = rx + (ry * 100);
    short contents[1200] = { 0 };
    rcol = 0;
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
        rn(50, 50), rn(50, 50), rn(50, 51), rn(50, 51), rn(49, 51), rn(49, 51),
        rn(49, 52), rn(49, 52), rn(48, 52), rn(48, 52), rn(48, 53), rn(48, 53),
        rn(49, 53), rn(49, 53), rn(50, 53), rn(50, 53), rn(51, 53), rn(51, 53),
        rn(52, 53), rn(52, 53), rn(52, 52), rn(52, 52), rn(51, 52), rn(51, 52),
        rn(51, 51), rn(51, 51), rn(51, 50), rn(51, 50), rn(52, 50), rn(52, 50),
        rn(52, 51), rn(52, 51), rn(53, 51), rn(53, 51), rn(53, 50), rn(53, 50),
        rn(54, 50), rn(54, 50), rn(54, 51), rn(54, 51), rn(55, 50), rn(55, 50),
        rn(55, 49), rn(55, 49), rn(55, 51), rn(55, 51), rn(55, 52), rn(55, 52),
        rn(55, 53), rn(55, 53), rn(55, 54), rn(55, 54), rn(54, 54), rn(54, 54),
        rn(53, 54), rn(53, 54), rn(52, 54), rn(52, 54), rn(51, 54), rn(51, 54),
        rn(50, 54), rn(50, 54), rn(49, 54), rn(49, 54), rn(49, 55), rn(49, 55),
        rn(50, 55), rn(50, 55), rn(51, 55), rn(51, 55), rn(52, 55), rn(52, 55),
        rn(52, 56), rn(52, 56), rn(52, 57), rn(52, 57), rn(50, 52), rn(50, 52),
        rn(53, 55), rn(53, 55), rn(54, 55), rn(54, 55), rn(52, 58), rn(52, 58),
        rn(51, 58), rn(51, 58), rn(50, 58), rn(50, 58)
    };

    auto key = std::to_string(t);
    if (level_table.contains(key)) {
#if !defined(MAKEANDPLAY)
        // parse data from json
        auto cur_level = level_table[key];
        roomname = cur_level["roomname"].get<std::string>();

        for (const auto& entity : cur_level["entities"])
            create_entity(entity);

        if (cur_level.contains("rcol"))
            rcol = cur_level["rcol"].get<int>();

        load_content_arr(cur_level["content"]);

        switch (t) {
            case rn(50, 50):
                if (game.intimetrial)
                    obj.createblock(0, 0, 0, 8, 240);
                break;

            case rn(49, 53):
                obj.createblock(5, 156 - 8, 128, 20, 16, 19);
                break;

            case rn(51, 52):
                obj.createblock(5, 204 - 8, 32, 20, 16, 20);
                break;

            case rn(55, 49):
                if (!game.intimetrial)
                    obj.createentity(
                        (12 * 8) - 4, (6 * 8) + 4, 14); // Teleporter!
                break;

            case rn(54, 54):
                obj.fatal_top();
                break;

            case rn(53, 54):
                obj.fatal_top();
                break;

            case rn(52, 54):
                obj.fatal_top();
                break;

            case rn(51, 54):
                obj.fatal_top();
                break;

            case rn(50, 54):
                obj.fatal_top();
                break;

            case rn(51, 58):
                if (!game.intimetrial) {
                    if (game.companion == 0 && !obj.flags[9] &&
                        !game.crewstats[5]) // also need to check if he's
                                            // rescued in a previous game
                    {
                        obj.createentity(32, 177, 18, 16, 1, 17, 1);
                        obj.createblock(1, 24 * 8, 0, 32, 240, 33);
                    }
                }
                break;

            case rn(50, 58):
                if (game.intimetrial)
                    obj.createblock(1, 280, 0, 32, 240, 82);
                break;

#endif
        }
    }
    return contents;
}
