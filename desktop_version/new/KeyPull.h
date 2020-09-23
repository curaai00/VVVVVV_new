#pragma once

// #include <SDL2/SDL.h>
#include "SDL.h"
#include <map>

class KeyPull
{
public:
    KeyPull();

    void pull(void);

    bool isDown(const SDL_Keycode k) const
    {
        if (keymap.find(k) != keymap.end())
            return keymap.at(k);
        return false;
    }
    bool isUp(const SDL_Keycode k) const
    {
        if (keymap.find(k) != keymap.end())
            return !keymap.at(k);
        return true;
    }

private:
    std::map<SDL_Keycode, bool> keymap;
};