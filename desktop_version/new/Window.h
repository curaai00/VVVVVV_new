#pragma once

#include "Background.h"
#include "KeyPull.h"

#include <SDL.h>

class Window
{
public:
    Window();

    void render(void);
    void event(const KeyPull& k);

    const int width = 320;
    const int height = 240;
    Background back;

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_screenTexture;
    SDL_Surface* m_screen;
};