#pragma once

#include "Background.h"
#include <SDL.h>

class Window
{
public:
    Window();

    void render(void);

    const int width = 320;
    const int height = 240;

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_screenTexture;
    SDL_Surface* m_screen;
    Background back;
};