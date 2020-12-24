#include <iostream>

#include "Game.h"
#include "KeyPull.h"
#include "Window.h"

#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <physfs.h>

volatile Uint32 f_time = 0;
volatile Uint32 f_timePrev = 0;
volatile Uint32 f_timetaken = 0;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK |
             SDL_INIT_GAMECONTROLLER);

    char *assetPath = argv[1];

    PHYSFS_init(assetPath);
    if (!PHYSFS_mount(assetPath, NULL, 1))
    {
        std::invalid_argument("AssetPath is Invalid");
    }
    auto win = Window();
    auto key = KeyPull();

    auto game = new Game{};
    win.set_scene(game);

    while (key.isUp(SDLK_ESCAPE))
    {
        f_time = SDL_GetTicks();

        key.pull();
        win.update(key);
        win.render();

        const Uint32 f_timetaken = f_time - f_timePrev;
        if (f_timetaken < 34)
        {
            const volatile Uint32 f_delay = 34 - f_timetaken;
            SDL_Delay(f_delay);
            f_time = SDL_GetTicks();
        }

        f_timePrev = f_time;
    }

    return 0;
}
