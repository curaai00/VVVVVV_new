#include "Menu.h"

SimpleMenu::SimpleMenu()
{
    // TODO replace init to another
    // char* assetsPath = NULL;
    char* assetsPath =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/data";
    // "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\Debug\\data";
    char* argvZero =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/VVVVVV_run";
    // "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\Debug\\data";
    FILESYSTEM_init(argvZero, argvZero, assetsPath);
    desc_table = parse_json("menu_description.json");
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