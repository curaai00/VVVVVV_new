#ifndef BLOCKV_H
#define BLOCKV_H

#include <SDL.h>
#include <algorithm>
#include <string>

struct RGB
{
    Uint8 r, g, b;
};
struct RGBA
{
    RGBA() {}
    RGBA(int r, int g, int b)
        : r(static_cast<Uint8>(r))
        , g(static_cast<Uint8>(g))
        , b(static_cast<Uint8>(b))
        , a(1.0f)
    {}
    RGBA(int r, int g, int b, float a)
        : RGBA(r, g, b)
    {
        a = std::min(1.0f, std::max(0.0f, a));
    }
    RGBA(const std::string& color_code)
    {
        // TODO HEX STRING
        if (color_code == "transparent")
            a = 0.0f;
        else if (color_code == "transparent_half")
            a = 0.5f;
        else
            return;
    }

    bool is_transparent(void) { return a == 0.0f; }
    bool is_half_transparent(void) { return a == 0.5f; }
    Uint8 r, g, b;
    float a = 0.0f;
};

class blockclass
{
public:
    blockclass();

    void rectset(const int xi, const int yi, const int wi, const int hi);

    void setblockcolour(std::string col);

public:
    // Fundamentals
    SDL_Rect rect;
    int type;
    int trigger;
    int xp, yp, wp, hp;
    std::string script, prompt;
    int r, g, b;

    // These would come from the sprite in the flash
    float x;
    float y;
};

#endif /* BLOCKV_H */
