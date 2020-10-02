#include <iostream>

#include "KeyPull.h"
#include "Message.h"
#include "Resource.h"
#include "Sprite.h"
#include "Window.h"

#include <SDL.h>
#include <physfs.h>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK |
             SDL_INIT_GAMECONTROLLER);

#ifdef __WIN32__
    char* assetPath =
        "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\data";
#else
    char* assetPath =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/data";
#endif
    PHYSFS_init(assetPath);
    if (!PHYSFS_mount(assetPath, NULL, 1)) {
        std::invalid_argument("AssetPath is Invalid");
    }

    Background back;
    Message msg{ SDL_Point{ 5, 175 },
                 SDL_Color{ 255, 0, 0, 255 },
                 "[ Press ACTION to Start ]",
                 true };
    // 23 is sprite idx of Big V
    SpriteSet titleSprite{ SDL_Point{ 64, 50 }, { 23, 23, 23, 23, 23, 23 } };

    Layer intro_layer;
    intro_layer.addDrawable(&msg);
    intro_layer.addDrawable(&titleSprite);

    auto win = Window();
    win.addScreenLayer(&back);
    win.addScreenLayer(&intro_layer);
    auto key = KeyPull();

    while (key.isUp(SDLK_ESCAPE)) {
        key.pull();
        win.key_event(key);

        win.render();
        SDL_Delay(50);

        back.scroll();
    }

    return 0;
}
