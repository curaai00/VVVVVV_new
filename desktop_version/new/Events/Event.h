#pragma once

#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class Event
{
public:
    virtual ~Event() = default;
    virtual void update(SDL_Keycode k) = 0;
};