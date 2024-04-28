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
        SDL_WINDOW_OPENGL);

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
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    std::cout << "Right mouse button is pressed" << std::endl;
                }
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    std::cout << "Left mouse button is pressed" << std::endl;
                }
                if (event.button.button == SDL_BUTTON_MIDDLE)
                {
                    std::cout << "Middle mouse button is pressed" << std::endl;
                }
                break;
            case SDL_MOUSEMOTION:
                int x{event.motion.x};
                int y{event.motion.y};
                std::cout << "Key Position (" << x << ", " << y << ")" << std::endl;
                break;
                /*case SDL_MOUSEWHEEL:
                    int x2{event.wheel.x};
                    int y2{event.wheel.y};
                    std::cout << "Mouse Scroll (" << x2 << ", " << y2 << ")" << std::endl;
                    break;*/
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}