#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Audio Library not working %s\n", Mix_GetError());
        return 1;
    }

    Mix_Music *music;
    music = Mix_LoadMUS("12_sdl-mixer/music.wav");
    if (!music)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load music %s\n", Mix_GetError());
        return 1;
    }

    bool isRunning = SDL_TRUE;
    bool shouldPlayMusic = SDL_FALSE;
    while (isRunning) // Infinite loop for the application
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) // Start the event loop
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    shouldPlayMusic = !shouldPlayMusic;
                    if (shouldPlayMusic)
                    {
                        Mix_PlayMusic(music, -1);
                    }
                    else
                    {
                        Mix_PlayMusic(music, 0);
                    }
                    std::cout << "Play/Pause music \n";
                }

                if (event.key.keysym.sym == SDLK_PLUS)
                {
                    Mix_VolumeMusic(75);
                }

                if (event.key.keysym.sym == SDLK_MINUS)
                {
                    Mix_VolumeMusic(25);
                }

                break;
            }
        }
    }

    Mix_FreeMusic(music);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}