#pragma once

#include "FileSystemUtils.h"
#include <SDL.h>
#include <json.hpp>

inline nlohmann::json parse_json(const char* path)
{
    unsigned char* uMem = NULL;
    FILESYSTEM_loadFileToMemory(path, &uMem, NULL, true);
    return nlohmann::json::parse(uMem);
}

// Menu IDs
namespace Menu {
enum name
{
    mainmenu,
    playerworlds,
    levellist,
    quickloadlevel,
    youwannaquit,
    errornostart,
    graphicoptions,
    ed_settings,
    ed_desc,
    ed_music,
    ed_quit,
    options,
    advancedoptions,
    accessibility,
    controller,
    cleardatamenu,
    setinvincibility,
    setslowdown,
    unlockmenu,
    credits,
    credits2,
    credits25,
    credits3,
    credits4,
    credits5,
    credits6,
    play,
    unlocktimetrial,
    unlocktimetrials,
    unlocknodeathmode,
    unlockintermission,
    unlockflipmode,
    newgamewarning,
    playmodes,
    intermissionmenu,
    playint1,
    playint2,
    continuemenu,
    startnodeathmode,
    gameover,
    gameover2,
    unlockmenutrials,
    timetrials,
    nodeathmodecomplete,
    nodeathmodecomplete2,
    timetrialcomplete,
    timetrialcomplete2,
    timetrialcomplete3,
    gamecompletecontinue,
};
inline std::string name2str(name name_)
{
    std::string str;
    switch (name_) {
        case mainmenu:
            str = "mainmenu";
            break;
        case playerworlds:
            str = "playerworlds";
            break;
        case levellist:
            str = "levellist";
            break;
        case quickloadlevel:
            str = "quickloadlevel";
            break;
        case youwannaquit:
            str = "youwannaquit";
            break;
        case errornostart:
            str = "errornostart";
            break;
        case graphicoptions:
            str = "graphicoptions";
            break;
        case ed_settings:
            str = "ed_settings";
            break;
        case ed_desc:
            str = "ed_desc";
            break;
        case ed_music:
            str = "ed_music";
            break;
        case ed_quit:
            str = "ed_quit";
            break;
        case options:
            str = "options";
            break;
        case advancedoptions:
            str = "advancedoptions";
            break;
        case accessibility:
            str = "accessibility";
            break;
        case controller:
            str = "controller";
            break;
        case cleardatamenu:
            str = "cleardatamenu";
            break;
        case setinvincibility:
            str = "setinvincibility";
            break;
        case setslowdown:
            str = "setslowdown";
            break;
        case unlockmenu:
            str = "unlockmenu";
            break;
        case credits:
            str = "credits";
            break;
        case credits2:
            str = "credits2";
            break;
        case credits25:
            str = "credits25";
            break;
        case credits3:
            str = "credits3";
            break;
        case credits4:
            str = "credits4";
            break;
        case credits5:
            str = "credits5";
            break;
        case credits6:
            str = "credits6";
            break;
        case play:
            str = "play";
            break;
        case unlocktimetrial:
            str = "unlocktimetrial";
            break;
        case unlocktimetrials:
            str = "unlocktimetrials";
            break;
        case unlocknodeathmode:
            str = "unlocknodeathmode";
            break;
        case unlockintermission:
            str = "unlockintermission";
            break;
        case unlockflipmode:
            str = "unlockflipmode";
            break;
        case newgamewarning:
            str = "newgamewarning";
            break;
        case playmodes:
            str = "playmodes";
            break;
        case intermissionmenu:
            str = "intermissionmenu";
            break;
        case playint1:
            str = "playint1";
            break;
        case playint2:
            str = "playint2";
            break;
        case continuemenu:
            str = "continuemenu";
            break;
        case startnodeathmode:
            str = "startnodeathmode";
            break;
        case gameover:
            str = "gameover";
            break;
        case gameover2:
            str = "gameover2";
            break;
        case unlockmenutrials:
            str = "unlockmenutrials";
            break;
        case timetrials:
            str = "timetrials";
            break;
        case nodeathmodecomplete:
            str = "nodeathmodecomplete";
            break;
        case nodeathmodecomplete2:
            str = "nodeathmodecomplete2";
            break;
        case timetrialcomplete:
            str = "timetrialcomplete";
            break;
        case timetrialcomplete2:
            str = "timetrialcomplete2";
            break;
        case timetrialcomplete3:
            str = "timetrialcomplete3";
            break;
        case gamecompletecontinue:
            str = "gamecompletecontinue";
            break;
    }
    return str;
};

constexpr int MAX_MENU_TEXT_BYTES = 161;

struct option
{
    option(const char* _text, bool _active)
    {
        SDL_strlcpy(text, _text, sizeof(text));
        active = _active;
    }

    char text[MAX_MENU_TEXT_BYTES]; // 40 chars (160 bytes) covers the entire
                                    // screen, + 1 more for null terminator
    // WARNING: should match Game::menutextbytes below
    bool active;
};

class Message
{
public:
    Message() {}
    Message(std::string text, int x, int y)
        : text(text)
        , x(x)
        , y(y)
    {}
    Message(const nlohmann::json& _json)
    {
        if (_json.contains("x"))
            x = _json["x"].get<int>();
        if (_json.contains("y"))
            y = _json["y"].get<int>();
        if (_json.contains("msg"))
            text = _json["msg"].get<std::string>();
    }

    std::string text;
    int x = -1;
    int y = -1;
};

class Description
{
public:
    Description(const nlohmann::json& _json)
    {
        main_msg = Message{ _json["main"] };
        for (auto element : _json["sub"]) {
            sub_msg.push_back(Message{ element });
        }
    }

    Message main_msg;
    std::vector<Message> sub_msg;
};

};

struct MenuStackFrame
{
    int option;
    enum Menu::name name;
};

class SimpleMenu
{
public:
    SimpleMenu();

    inline void add_option(const char* text, bool active = true)
    {
        options.push_back(Menu::option{ text, active });
    }

    inline void increase_opt_idx(void)
    {
        if (++cur_option_idx >= (int)options.size())
            cur_option_idx = 0;
    }

    inline void decrease_opt_idx(void)
    {
        if (--cur_option_idx < 0)
            cur_option_idx = options.size() - 1;
    }

    bool hasSimpleDescMsg(void) const;
    bool hasSimpleDescMsg(Menu::name name, int option_idx) const;
    Menu::Description getDescriptionMsg(void);
    Menu::Description getDescriptionMsg(Menu::name name, int option_idx);

    int cur_option_idx;
    Menu::name cur_option_name;
    std::vector<Menu::option> options;

    Menu::name kludge_ingametemp;

    int xoff;
    int yoff;
    int spacing;

    int countdown;
    Menu::name destination;

    nlohmann::json desc_table;
};