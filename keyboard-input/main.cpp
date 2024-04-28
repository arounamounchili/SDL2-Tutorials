#include <SDL2/SDL.h>
#include <iostream>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Unable to initialize: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = nullptr;
    window = SDL_CreateWindow(
        "My app",
        50,
        50,
        640,
        480,
        SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window %s\n", SDL_GetError());
        return 1;
    }

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) // Poll until all events are handled
        {
            switch (event.type)
            { // Handle each specific event
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }

                if (event.key.keysym.sym == SDLK_a)
                {
                    std::cout << "Keyboard letter a is pressed\n";
                }
                if (event.key.keysym.sym == SDLK_1)
                {
                    std::cout << "1 was pressed\n";
                }
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}