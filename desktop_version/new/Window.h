#pragma once

#include "Background.h"
#include "Eventable.h"
#include "Message.h"

#include <SDL.h>

class Window : public EventCompsitor
{
public:
    Window();

    void render(void);
    void key_event(const KeyPull& key_pull);

    const int width = 320;
    const int height = 240;
    Background back;
    Message msg{ SDL_Point{ 100, 50 }, SDL_Color{ 255, 0, 0, 255 }, "VVVVVV" };

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_screenTexture;
    SDL_Surface* m_screen;
};