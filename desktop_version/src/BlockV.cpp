#include "BlockV.h"
#include <unordered_map>

blockclass::blockclass()
{
    type = 0;
    trigger = 0;

    xp = 0;
    yp = 0;
    wp = 0;
    hp = 0;
    rect.x = xp;
    rect.y = yp;
    rect.w = wp;
    rect.h = hp;

    r = 0;
    g = 0;
    b = 0;

    x = 0.0f;
    y = 0.0f;
}

void blockclass::rectset(const int xi, const int yi, const int wi, const int hi)
{
    rect.x = xi;
    rect.y = yi;
    rect.w = wi;
    rect.h = hi;
}

void blockclass::setblockcolour(std::string name)
{
    const std::unordered_map<std::string, RGB> color_table{
        { "cyan", { 164, 164, 255 } },  { "red", { 255, 60, 60 } },
        { "green", { 144, 255, 144 } }, { "yellow", { 255, 255, 134 } },
        { "blue", { 95, 95, 255 } },    { "purple", { 255, 134, 255 } },
        { "white", { 244, 244, 244 } }, { "gray", { 174, 174, 174 } },
        { "orange", { 255, 130, 20 } }
    };

    RGB rgb;
    auto find_res = color_table.find(name);
    if (find_res != color_table.end())
        rgb = find_res->second;
    else
        rgb = RGB{ 174, 174, 174 };

    r = rgb.r;
    g = rgb.g;
    b = rgb.b;
}
