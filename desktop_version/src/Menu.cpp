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
    return hasSimpleDescMsg(cur_option_name, cur_option_idx);
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
    return getDescriptionMsg(cur_option_name, cur_option_idx);
}
Menu::Description SimpleMenu::getDescriptionMsg(Menu::name name, int option_idx)
{
    return desc_table[Menu::name2str(name)][option_idx];
}