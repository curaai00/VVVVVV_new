#pragma once

#include "Entity.h"
#include "Game.h"
#include "KeyPull.h"
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
    // Update key based input first, input should pre-processed and rendering
    void update(KeyPull &pull)
    {
        auto pressed_keys = pull.pressedKeys();
        for (auto k : pressed_keys)
            scene->EventEntities::update(k);

        scene->Layers::update();
    }

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