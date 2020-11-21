#include <iostream>

#include "KeyPull.h"
#include "Menu.h"
#include "Window.h"

#include <SDL.h>
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

    win.set_game(new Menu{});

    while (key.isUp(SDLK_SPACE))
    {
        key.pull();
        win.update();
        win.render();
        SDL_Delay(50);
    }

    return 0;
}
