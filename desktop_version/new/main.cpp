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

    win.set_scene(new Game{});

    while (key.isUp(SDLK_SPACE))
    {
        key.pull();
        win.update(key);
        win.render();
        SDL_Delay(50);
    }

    return 0;
}
