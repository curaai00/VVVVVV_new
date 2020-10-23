#pragma once

#include "Entity.h"

#include <SDL.h>
#include <vector>

class Window : public Compositor<Layer, void>
{
public:
    Window();
    ~Window();

    void render(void);
    void update(void) { entity->update(); }
    // void key_event(const KeyPull &key_pull) { game->key_event(key_pull); }

    // void setGame(Game *_game) { game = _game; }

    const int width = 320;
    const int height = 240;

    DrawableEntity *entity = nullptr;

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_screenTexture;
    SDL_Surface *m_screen;
};