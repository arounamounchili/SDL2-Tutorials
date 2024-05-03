#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
        SDL_WINDOW_RESIZABLE);

    // Check that the window was successfully created
    if (window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Coud not create window: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer in order for draw calls to affect this window
    SDL_Renderer *renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Coud not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    // Load support for the the JPG and PNG image formats
    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to init required png and jpg support: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Surface *image = nullptr;
    image = IMG_Load("10_sdl-image/image.png");
    if (!image)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "IMG_Load: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture *pngTexture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

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
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, pngTexture, NULL, NULL);

            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyTexture(pngTexture);
    IMG_Quit(); // Unload the dynamically loaded image libraries
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}