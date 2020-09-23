#include "Menu.h"

SimpleMenu::SimpleMenu()
{
    // TODO replace init to another
    // char* assetsPath = NULL;
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
    desc_table = parse_json("menu_description.json");
}

void SimpleMenu::go(SelectBoard sb, bool samemenu)
{
    countdown = 0;

    if (sb.cur_option_name == Menu::mainmenu) {
        while (!board_stack.empty())
            board_stack.pop();
    } else if (!samemenu) {
        board_stack.push(curBoard);
    }

    curBoard = sb;
}
void SimpleMenu::back(void)
{
    if (!board_stack.empty()) {
        curBoard = board_stack.top();
        board_stack.pop();
    }
}

void SimpleMenu::back(enum Menu::name t)
{
    if (getCurOptName() == t)
        return;
    while (!board_stack.empty()) {
        back();
        if (getCurOptName() == t)
            break;
    }
}

bool SimpleMenu::isNameContain(Menu::name m) const
{
    auto temp_stack = board_stack;
    while (!temp_stack.empty()) {
        if (temp_stack.top().cur_option_name == m)
            return true;
        temp_stack.pop();
    }
    return false;
}

bool SimpleMenu::hasSimpleDescMsg() const
{
    return hasSimpleDescMsg(getCurOptName(), getCurOptIdx());
}

bool SimpleMenu::hasSimpleDescMsg(Menu::name name, int option_idx) const
{
    auto str_name = Menu::name2str(name);
    if (!desc_table.contains(str_name))
        return false;
    auto size = desc_table[str_name].size();
    return size > 0 && size > option_idx;
}

Menu::Description SimpleMenu::getDescriptionMsg(void)
{
    return getDescriptionMsg(getCurOptName(), getCurOptIdx());
}
Menu::Description SimpleMenu::getDescriptionMsg(Menu::name name, int option_idx)
{
    return desc_table[Menu::name2str(name)][option_idx];
}

SelectBoard::SelectBoard()
{
    xoff = 0;
    yoff = 0;
    spacing = 0;
    cur_option_idx = 0;
    cur_option_name = Menu::mainmenu;
}