#include "Finalclass.h"

#include "Entity.h"
#include "FileSystemUtils.h"
#include "Game.h"
#include "MakeAndPlay.h"
#include "UtilityClass.h"

finalclass::finalclass()
{ // TODO replace init to another
    // char* assetsPath = NULL;
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
    level_table = parse_json("final_level.json");
}

const short* finalclass::loadlevel(int rx, int ry)
{
    int t;

    t = rx + (ry * 100);
    const short* result;
    warpx = false;
    warpy = false;

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
        rn(53, 48), rn(53, 49), rn(52, 56),   rn(53, 56),   rn(50, 56),
        rn(45, 56), rn(47, 56), rn(48, 56),   rn(53, 52),   rn(41, 56),
        rn(48, 52), rn(50, 53), rn(50, 54),   rn(52, 53),   rn(53, 53),
        rn(54, 53), rn(54, 52), rn(54, 51),   rn(54, 50),   rn(54, 49),
        rn(46, 54), rn(47, 54), rn(48, 54),   rn(49, 54),   rn(108, 109),
        rn(41, 52), rn(54, 48), rn(110, 104), rn(111, 104), rn(53, 50),
        rn(53, 51), rn(42, 56), rn(43, 56),   rn(44, 56),   rn(46, 56),
        rn(49, 56), rn(51, 56), rn(54, 56)
    };

    auto key = std::to_string(t);
    if (level_table.contains(key)) {
#if !defined(MAKEANDPLAY)
        // parse data from json
        auto cur_level = level_table[key];
        roomname = cur_level["roomname"].get<std::string>();

        for (const auto& entity : cur_level["entities"])
            create_entity(entity);

        if (cur_level.contains("warpx"))
            warpx = cur_level["warpx"].get<bool>();
        if (cur_level.contains("warpy"))
            warpy = cur_level["warpy"].get<bool>();

        load_content_arr(cur_level["content"]);

        switch (t) {
            case rn(41, 52):
                if (!obj.flags[72]) {
                    if (game.intimetrial || game.nocutscenes)
                        obj.createblock(1, 152 - 4, 112, 20, 16, 85);
                    else
                        obj.createblock(5, 152 - 4, 112, 20, 16, 13);
                }
                break;

            case rn(54, 48):
                obj.createblock(0, 0, 0, 5, 240);
                obj.createblock(0, 315, 0, 5, 240);

                if (game.intimetrial)
                    obj.createblock(1, 0, 0, 320, 120, 82);
                else
                    obj.createblock(1, 0, 0, 320, 120, 3500); // Game complete
                break;

            case rn(110, 104):
                if (!game.intimetrial) {
                    if (game.companion == 0 && !obj.flags[8] &&
                        !game.crewstats[3]) // also need to check if he's
                                            // rescued in a previous game
                    {
                        obj.createentity(264, 185, 18, 15, 1, 17, 0);
                        obj.createblock(1, 26 * 8, 0, 32, 240, 36);
                    }
                }
                break;

            case rn(111, 104):
                if (game.intimetrial)
                    obj.createblock(1, 40, 0, 32, 240, 82);
                break;

            case rn(53, 50):

                // obj.createentity(-8, 84-32, 11, 328);  // (horizontal
                // gravity line)
                obj.createentity(
                    -8, 148 + 32, 11, 328); // (horizontal gravity line)

                obj.createblock(1,
                                -10,
                                84 - 16,
                                340,
                                32,
                                10); // create the second line!

                break;

            case rn(53, 51):
                if (game.companion == 0) // also need to check if he's
                                         // rescued in a previous game
                {
                    if (game.lastsaved == 2) {
                        obj.createentity(112, 169, 18, 14, 0, 17, 1);
                        obj.createblock(1, 22 * 8, 16 * 8, 32, 240, 37);
                    } else if (game.lastsaved == 3) {
                        obj.createentity(112, 169, 18, 15, 0, 17, 1);
                        obj.createblock(1, 22 * 8, 16 * 8, 32, 240, 38);
                    } else if (game.lastsaved == 4) {
                        obj.createentity(112, 169, 18, 13, 0, 17, 1);
                        obj.createblock(1, 22 * 8, 16 * 8, 32, 240, 39);
                    } else {
                        obj.createentity(112, 169, 18, 16, 1, 17, 1);
                        obj.createblock(1, 22 * 8, 16 * 8, 32, 240, 40);
                    }
                }
                game.swnmode = false;
                break;
            case rn(42, 56):
                if (!game.nodeathmode) {
                    obj.createblock(1, 0, 0, 32, 240, 41);   // scene 2
                    obj.createblock(1, 280, 0, 32, 240, 12); // scene 2
                }
                break;
            case rn(43, 56):
                if (!game.nodeathmode)
                    obj.createblock(1, 20, 0, 32, 240, 13); // scene 2
                break;
            case rn(44, 56):
                if (!game.nodeathmode)
                    obj.createblock(1, 200, 0, 32, 240, 42); // scene 3
                break;
            case rn(46, 56):
                if (!game.nodeathmode)
                    obj.createblock(1, 200, 0, 32, 240, 43); // scene 3
                break;
            case rn(49, 56):
                if (!game.nodeathmode)
                    obj.createblock(1, 200, 0, 32, 240, 44); // scene 3
                break;
            case rn(51, 56):
                if (!game.nodeathmode)
                    obj.createblock(1, 80, 0, 32, 240, 45); // scene 3
                break;
            case rn(54, 56):
                if (!game.nodeathmode)
                    obj.createblock(1, 104, 0, 32, 240, 46); // scene 3
                break;
        }
#endif
    } else {
        roomname = "Outer Space";
    }

    result = contents;

    return result;
}
