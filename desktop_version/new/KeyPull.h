#pragma once

#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <map>
#include <vector>

// TODO: Add occupy table
class KeyPull
{
public:
    KeyPull();

    void pull(void);

    bool isDown(const SDL_Keycode k) const
    {
        if (keymap.find(k) != keymap.end()) return keymap.at(k);
        return false;
    }
    bool isUp(const SDL_Keycode k) const
    {
        if (keymap.find(k) != keymap.end()) return !keymap.at(k);
        return true;
    }
    std::vector<SDL_Keycode> pressedKeys(void) const
    {
        std::vector<SDL_Keycode> keys;
        for (auto k_iter = keymap.begin(); k_iter != keymap.end(); k_iter++)
            if (k_iter->second) keys.push_back(k_iter->first);
        return keys;
    }

private:
    std::map<SDL_Keycode, bool> keymap;
};