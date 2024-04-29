#include <SDL2/SDL.h>

int main()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO != 0))
    {
        SDL_Log("Unable to initialize: %s", SDL_GetError());
        return 1;
    }

    // Create the window where we will draw
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

    // Create a renderer in order for draw calls to affect this window
    SDL_Renderer *renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Coud not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    // Create a rectangle
    SDL_Rect rectangle;
    rectangle.w = 50;
    rectangle.h = 30;
    rectangle.x = 100;
    rectangle.y = 150;

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                break;
            }
            // Select a color for drawing. It is set to black color
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            // Clear the entire screen to our selected color.
            SDL_RenderClear(renderer);

            // Draw a line with a white color
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(renderer, 5, 5, 100, 150);

            // Draw a rectangle
            SDL_RenderDrawRect(renderer, &rectangle);

            // Up until now everything was drawn behind the scenes.
            // This will show the new contents of the window
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}