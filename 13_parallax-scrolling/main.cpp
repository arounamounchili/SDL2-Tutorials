#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH = 801;
const int SCREEN_HEIGHT = 601;

/**
 * @brief Initialize SDL, creates a window and a renderer, and
 * initialize SDL_image for PNG support
 *
 * @param window the the window where rendering is displayed
 * @param renderer the rendering context
 * @return true if success
 * @return false if faillure
 */
bool init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL could not initialze! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *window = SDL_CreateWindow(
        "Parallax Scrolling",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (*window == nullptr)
    {
        std::cout << "Window could not be created! SDL_ERROR: " << SDL_GetError() << std::endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_ERROR: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "SDL_image could not be initialize! IMG_ERROR: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Load a PNG image and converts it to an SDL texture
 *
 * @param path the path of image
 * @param renderer the rendering context
 * @return SDL_Texture* the image as texture
 */
SDL_Texture *loadTexture(const std::string &path, SDL_Renderer *renderer)
{
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image " << path << "! IMG_Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr)
        {
            std::cout << "Unable to create texture from " << path << "! SDL_Error: " << IMG_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

// Main function
int main(int argc, char *argv[])
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (!init(&window, &renderer))
    {
        std::cout << "Failed to initialize!\n";
        return -1;
    }

    SDL_Texture *bgLayer1 = loadTexture("13_parallax-scrolling/image/sky.png", renderer);
    SDL_Texture *bgLayer2 = loadTexture("13_parallax-scrolling/image/obstacle.png", renderer);
    SDL_Texture *bgLayer3 = loadTexture("13_parallax-scrolling/image/ground.png", renderer);

    if (bgLayer1 == nullptr || bgLayer2 == nullptr || bgLayer3 == nullptr)
    {
        std::cout << "Failed to load textures!\n";
        return -1;
    }

    int layer1Offset = 0;
    int layer2Offset = 0;
    int layer3Offset = 0;
    const int layer1Speed = 1;
    const int layer2Speed = 2;
    const int layer3Speed = 4;

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

        layer1Offset -= layer1Speed;
        layer2Offset -= layer2Speed;
        layer3Offset -= layer3Speed;

        if (layer1Offset <= -SCREEN_WIDTH)
        {
            layer1Offset = 0;
        }
        if (layer2Offset <= -SCREEN_WIDTH)
        {
            layer2Offset = 0;
        }
        if (layer3Offset <= -SCREEN_WIDTH)
        {
            layer3Offset = 0;
        }

        SDL_RenderClear(renderer);

        // Little delay
        // SDL_Delay(15);

        /*Each layer is rendered twice to create a seamless scrolling effect. When the offset goes past the width of the screen, it resets to zero.*/
        SDL_Rect rect = {layer1Offset, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, bgLayer1, nullptr, &rect);
        rect.x = layer1Offset + SCREEN_WIDTH;
        SDL_RenderCopy(renderer, bgLayer1, nullptr, &rect);

        rect = {layer2Offset, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, bgLayer2, nullptr, &rect);
        rect.x = layer2Offset + SCREEN_WIDTH;
        SDL_RenderCopy(renderer, bgLayer2, nullptr, &rect);

        rect = {layer3Offset, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, bgLayer3, nullptr, &rect);
        rect.x = layer3Offset + SCREEN_WIDTH;
        SDL_RenderCopy(renderer, bgLayer3, nullptr, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bgLayer1);
    SDL_DestroyTexture(bgLayer2);
    SDL_DestroyTexture(bgLayer3);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}