#include "KeyPull.h"

KeyPull::KeyPull() {}

void KeyPull::pull(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // if (event.key.repeat) continue;

        switch (event.type)
        {
        case SDL_KEYDOWN:
            keymap[event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            keymap[event.key.keysym.sym] = false;
            break;
        }
    }
}