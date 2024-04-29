#include <SDL2/SDL.h>
#include <iostream>

void SetWindowPixel(SDL_Surface *surface, int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    SDL_LockSurface(surface);
    uint8_t *pixelArray = (uint8_t *)surface->pixels;
    pixelArray[y * surface->pitch + x * surface->format->BytesPerPixel + 0] = g;
    pixelArray[y * surface->pitch + x * surface->format->BytesPerPixel + 1] = b;
    pixelArray[y * surface->pitch + x * surface->format->BytesPerPixel + 2] = r;
    SDL_UnlockSurface(surface);
}

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

    // Grap the window surface
    SDL_Surface *screen;
    screen = SDL_GetWindowSurface(window);
    if (screen == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create surface %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *image;
    image = SDL_LoadBMP("create-surface/panda.bmp"); // loads image
    if (image == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not load a BMP image %s\n", SDL_GetError());
        return 1;
    }
    SDL_BlitSurface(image, NULL, screen, NULL); // blit it to the screen
    SDL_FreeSurface(image);
    SDL_UpdateWindowSurface(window);

    bool isRunning = SDL_TRUE;
    while (isRunning)
    {
        SDL_Event event;

        int x, y;
        SDL_GetMouseState(&x, &y);

        while (SDL_PollEvent(&event)) // Poll until all events are handled
        {
            switch (event.type)
            { // Handle each specific event
            case SDL_QUIT:
                isRunning = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = SDL_FALSE;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SetWindowPixel(screen, x, y, 255, 0, 0);
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    SetWindowPixel(screen, x, y, 0, 0, 255);
                }
                break;
            }
        }
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}