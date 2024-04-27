#include <SDL2/SDL.h>

int main()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO != 0))
    {
        SDL_Log("Unable to initialize: %s", SDL_GetError());
        return 1;
    }

    // Create an application window
    SDL_Window *window = nullptr;
    window = SDL_CreateWindow(
        "SDL Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    // Check that the window was successfully created
    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Coud not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Delay(5000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}