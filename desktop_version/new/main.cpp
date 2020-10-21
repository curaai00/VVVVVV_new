#include <iostream>

#include "Components/BackgroundComponent.h"
#include "KeyPull.h"
#include "Window.h"

#include <SDL.h>
#include <physfs.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK |
             SDL_INIT_GAMECONTROLLER);

#ifdef __WIN32__
    char *assetPath = "C:\\Users\\psjeong\\Documents\\VVVVVV\\desktop_version\\data";
#else
    char *assetPath =
        "/Users/jeongpilseong/workspace/proj/VVVVVV/desktop_version/data";
#endif
    PHYSFS_init(assetPath);
    if (!PHYSFS_mount(assetPath, NULL, 1))
    {
        std::invalid_argument("AssetPath is Invalid");
    }
    auto win = Window();
    auto key = KeyPull();

    Layer layer;

    DrawableEntity *entity = new DrawableEntity();
    StripeComponent stripe;
    DrawToComponent draw({layer->surface(), NULL}, {stripe->surface(), NULL});
    entity->add(&stripe)->add(&draw)->set_surface(stripe->surface());

    win.entity = entity;

    while (key.isUp(SDLK_SPACE))
    {
        key.pull();
        win.render();
        SDL_Delay(50);
    }

    return 0;
}
