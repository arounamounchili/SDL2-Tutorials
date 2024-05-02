#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO != 0))
    {
        SDL_Log("Unable to initialize: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = nullptr;
    window = SDL_CreateWindow(
        "Watter Effect",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize TTF
    if (TTF_Init() != 0)
    {
        SDL_Log("Unable to Initiale %s:", SDL_GetError());
        exit(1);
    }

    // Load a font file and set the font size
    TTF_Font *font = TTF_OpenFont("9_true-type-fonts/waltographUI.ttf", 24);
    TTF_Font *font2 = TTF_OpenFont("9_true-type-fonts/display.ttf", 24);

    if (font == NULL || font2 == NULL)
    {
        SDL_Log("Unable to load font %s:", SDL_GetError());
        exit(1);
    }

    // Pixels from our text
    SDL_Surface *surfaceText = TTF_RenderText_Solid(font, "Minteligencia Font", {255, 255, 255});
    SDL_Surface *surfaceText2 = TTF_RenderText_Solid(font2, "24:00 CHRONO", {255, 255, 0});
    // Setup de texture
    SDL_Texture *textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_Texture *textureText2 = SDL_CreateTextureFromSurface(renderer, surfaceText2);
    // Free the surface
    SDL_FreeSurface(surfaceText);
    SDL_FreeSurface(surfaceText2);

    // Create a rectangle
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 50;
    rectangle.w = 350;
    rectangle.h = 100;

    SDL_Rect rectangle2;
    rectangle2.x = 50;
    rectangle2.y = 200;
    rectangle2.w = 350;
    rectangle2.h = 100;

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
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Render our text on a rectangle
        SDL_RenderCopy(renderer, textureText, NULL, &rectangle);
        SDL_RenderCopy(renderer, textureText2, NULL, &rectangle2);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textureText);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}