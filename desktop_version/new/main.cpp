#include <iostream>

#include <SDL.h>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK |
             SDL_INIT_GAMECONTROLLER);

    std::cout << "Hello World" << std::endl;
    return 0;
}