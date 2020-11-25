#pragma once

#include "Entity.h"
#include "Scene.h"

#ifdef __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <vector>

class Window
{
public:
    Window();
    ~Window();

    void render(void);
    void update(void) { scene->update(); }
    // void key_event(const KeyPull &key_pull) { game->key_event(key_pull); }

    void set_scene(Scene *_scene) { scene = _scene; }

    const int width = 320;
    const int height = 240;

private:
    Scene *scene;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_screenTexture;
    SDL_Surface *m_screen;
};