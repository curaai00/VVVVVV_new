#pragma once

#include "KeyPull.h"
#include <vector>

class Eventable
{
public:
    virtual bool event(const SDL_Keycode k) = 0;
};

class EventCompsitor : public Eventable
{
public:
    inline bool event(const SDL_Keycode k) override
    {
        for (Eventable* obj : eventables)
            if (obj->event(k))
                return true;
        return false;
    };
    inline void addEventable(Eventable* obj) { eventables.push_back(obj); }
    inline void rmEventable(Eventable* obj)
    {
        for (auto it = eventables.begin(); it != eventables.end(); it++)
            if (*it == obj)
                eventables.erase(it);
    }

protected:
    std::vector<Eventable*> eventables;
};