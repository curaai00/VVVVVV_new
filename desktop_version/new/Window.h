#pragma once

#include "Background.h"
#include "Drawable.h"
#include "Eventable.h"
#include "Message.h"

#include <SDL.h>
#include <vector>

class Window : public EventCompsitor
{
public:
    Window();

    void render(void);
    void key_event(const KeyPull& key_pull);

    const int width = 320;
    const int height = 240;

    inline void addScreenLayer(ScreenDrawable* screen)
    {
        screen_layers.push_back(screen);
    };

private:
    std::vector<ScreenDrawable*> screen_layers;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_screenTexture;
    SDL_Surface* m_screen;
};