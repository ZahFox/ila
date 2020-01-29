#include "Window.h"

#include <SDL2/SDL.h>

namespace Ila {

static SDL_Window* window = nullptr;

Window::Window(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, width, height, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(5000);
}

Window::~Window()
{
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
}
