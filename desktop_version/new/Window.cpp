#include "Window.h"
#include "Resource.h"

Window::Window()
{
    SDL_CreateWindowAndRenderer(
        width, height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);
    m_screen = SDL_CreateRGBSurface(0, width, height, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    m_screenTexture = SDL_CreateTexture(
        m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    SDL_SetWindowTitle(m_window, "VVVVVV");
    auto icon = PNGAsset("VVVVVV.png");
    SDL_SetWindowIcon(m_window, icon.asset);
}
Window::~Window()
{

    SDL_FreeSurface(m_screen);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_screenTexture);
    SDL_DestroyWindow(m_window);
}

void Window::render(void)
{
    if (game) {
        game->draw();
        SDL_Surface* surface = game->surface();

        SDL_UpdateTexture(m_screenTexture, NULL, surface->pixels, surface->pitch);
        SDL_RenderCopy(m_renderer, m_screenTexture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
        SDL_RenderClear(m_renderer);
        SDL_FillRect(m_screen, NULL, 0x00000000);
    }
}
