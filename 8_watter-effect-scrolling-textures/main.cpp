#include <SDL2/SDL.h>

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
        SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load a surface from a file
    SDL_Surface *surface = SDL_LoadBMP("8_watter-effect-scrolling-textures/seamless-texture.bmp");

    // Create a texture from an existing surface.
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Create a rectangle
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 640;
    rectangle.h = 480;

    SDL_Rect rectangle2;
    rectangle2.x = -639;
    rectangle2.y = 0;
    rectangle2.w = 640;
    rectangle2.h = 480;

    SDL_Rect rectangle3;
    rectangle3.x = 0;
    rectangle3.y = 0;
    rectangle3.w = 640;
    rectangle3.h = 480;

    SDL_Rect rectangle4;
    rectangle4.x = 0;
    rectangle4.y = -479;
    rectangle4.w = 640;
    rectangle4.h = 480;

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
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_ADD);
                }
                else if (event.button.button == SDL_BUTTON_MIDDLE)
                {
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_BLEND);
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_MOD);
                }
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_Delay(25); // To slow down the simulation

        // Handle texture scrolling left to right
        rectangle.x++;
        if (rectangle.x > 639)
        {
            rectangle.x = -639;
        }
        rectangle2.x++;
        if (rectangle2.x > 639)
        {
            rectangle2.x = -639;
        }

        rectangle3.y++;
        if (rectangle3.y > 479)
        {
            rectangle3.y = -479;
        }
        rectangle4.y++;
        if (rectangle4.y > 479)
        {
            rectangle4.y = -479;
        }

        // Order matters
        // Scrolling left and right
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);
        SDL_RenderCopy(renderer, texture, NULL, &rectangle2);
        // Scrolling up and down
        SDL_RenderCopy(renderer, texture2, NULL, &rectangle3);
        SDL_RenderCopy(renderer, texture2, NULL, &rectangle4);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}