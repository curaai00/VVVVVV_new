#include "Window.h"
#include "Resource.h"

Window::Window()
{
    SDL_CreateWindowAndRenderer(
        width, height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);
    m_screen = SDL_CreateRGBSurface(
        0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    m_screenTexture = SDL_CreateTexture(m_renderer,
                                        SDL_PIXELFORMAT_ARGB8888,
                                        SDL_TEXTUREACCESS_STREAMING,
                                        width,
                                        height);

    SDL_SetWindowTitle(m_window, "VVVVVV");
    auto icon = PNGAsset("VVVVVV.png");
    SDL_SetWindowIcon(m_window, icon.asset);
}

void Window::render(void)
{
    back.draw();
    SDL_BlitSurface(back.surface, NULL, m_screen, NULL);

    SDL_UpdateTexture(m_screenTexture, NULL, m_screen->pixels, m_screen->pitch);
    SDL_RenderCopy(m_renderer, m_screenTexture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
    SDL_RenderClear(m_renderer);
    SDL_FillRect(m_screen, NULL, 0x00000000);
}