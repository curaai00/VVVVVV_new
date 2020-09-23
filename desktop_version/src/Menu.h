#pragma once

#include "BlockV.h"
#include "FileSystemUtils.h"
#include <SDL.h>
#include <json.hpp>
#include <stack>

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
        : _text(text)
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
            _text = _json["msg"].get<std::string>();
        if (_json.contains("color"))
            _color = RGBA{ _json["color"].get<std::string>() };
        if (_json.contains("type"))
            _type = _json["type"].get<std::string>();
    }

    virtual std::string text(void) const { return _text; }
    virtual RGBA color(void) const { return _color; }
    inline std::string type(void) const { return _type; }

    int x = -1;
    int y = -1;

protected:
    RGBA _color;
    std::string _type = "simple";
    std::string _text;
};

class ToggleMessage : public Message
{
public:
    ToggleMessage(const nlohmann::json& _json)
        : Message(_json)
    {
        _text_sub = _json["msg_sub"].get<std::string>();
        if (_json.contains("color_sub"))
            _color = RGBA{ _json["color_sub"].get<std::string>() };
    }

    std::string text(void) const override
    {
        return toggle_on ? _text : _text_sub;
    }
    RGBA color(void) const override { return toggle_on ? _color : _color_sub; }
    void set_toggle(bool _toggle_on) { toggle_on = _toggle_on; }

protected:
    bool toggle_on = true;
    std::string _text_sub;
    RGBA _color_sub;
};

class ListMessage : public Message
{
public:
    ListMessage(const nlohmann::json& _json)
        : Message(_json)
    {
        for (auto str : _json["msg_list"])
            _text_list.push_back(str.get<std::string>());
    }

    std::string text(void) const override { return _text_list[idx]; }
    void set_index(int _idx) { idx = _idx; }

protected:
    std::vector<std::string> _text_list;
    int idx;
};

inline Message* msgFactory(const nlohmann::json& _json)
{
    if (!_json.contains("type"))
        return new Message{ _json };
    else if (_json["type"].get<std::string>() == "toggle")
        return new ToggleMessage{ _json };
    else if (_json["type"].get<std::string>() == "list")
        return new ListMessage{ _json };

    return new Message{ _json };
};

class Description
{
public:
    Description(const nlohmann::json& _json)
    {
        for (auto element : _json["main"]) {
            main_msg.push_back(msgFactory(element));
        }
        for (auto element : _json["sub"]) {
            sub_msg.push_back(msgFactory(element));
        }
    }
    virtual ~Description(void)
    {
        for (auto main : main_msg)
            delete main;
        for (auto sub : sub_msg)
            delete sub;
    }

    std::vector<Message*> main_msg;
    std::vector<Message*> sub_msg;
};

};

class SelectBoard
{
public:
    SelectBoard();

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

    inline void add_option(const char* text, bool active = true)
    {
        options.push_back(Menu::option{ text, active });
    }

    int cur_option_idx;
    Menu::name cur_option_name;
    std::vector<Menu::option> options;

    int xoff;
    int yoff;
    int spacing;
};

class SimpleMenu
{
public:
    SimpleMenu();

    void init(void)
    {
        countdown = 0;
        kludge_ingametemp = Menu::mainmenu;
    }

    void go(SelectBoard sb, bool samemenu = false);
    void back(void);
    void back(enum Menu::name t);

    void setCurBoard(const SelectBoard& board) { curBoard = board; }
    const SelectBoard& getCurBoard() { return curBoard; }

    inline void increase_opt_idx(void) { curBoard.increase_opt_idx(); }
    inline void decrease_opt_idx(void) { curBoard.decrease_opt_idx(); }

    bool isNameContain(Menu::name m) const;
    Menu::name getCurOptName(void) const { return curBoard.cur_option_name; }
    int getCurOptIdx(void) const { return curBoard.cur_option_idx; }
    void setCurOptIdx(int idx) { curBoard.cur_option_idx = idx; }
    int getCurOptSize(void) { return curBoard.options.size(); }

    bool hasSimpleDescMsg(void) const;
    bool hasSimpleDescMsg(Menu::name name, int option_idx) const;
    Menu::Description getDescriptionMsg(void);
    Menu::Description getDescriptionMsg(Menu::name name, int option_idx);

    Menu::name kludge_ingametemp;

    int countdown;
    Menu::name destination;

    nlohmann::json desc_table;

private:
    std::stack<SelectBoard> board_stack;
    SelectBoard curBoard;
};