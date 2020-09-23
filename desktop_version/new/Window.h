#pragma once

#include "SDL.h"
// #include <SDL2/SDL.h>

class Window
{
public:
    Window(int w, int h);

    void render(void);

    int width;
    int height;

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_screenTexture;
    SDL_Surface* m_screen;
};