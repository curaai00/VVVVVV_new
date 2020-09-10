#include "Menu.h"

nlohmann::json SimpleMenu::desc_table;

SimpleMenu::SimpleMenu()
{
    // TODO replace init to another
    char* assetsPath = NULL;
    char* argvZero =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/data";
    // "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\Debug\\data";
    FILESYSTEM_init(argvZero, argvZero, assetsPath);
    desc_table = parse_json("menu_description.json");
}

bool SimpleMenu::hasSimpleDescMsg(Menu::name name, int option_idx)
{
    auto size = desc_table[Menu::name2str(name)].size();
    return size > 0 && size > option_idx;
}