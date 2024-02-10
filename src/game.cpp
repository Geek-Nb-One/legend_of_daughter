#include "game.hpp"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "constant.hpp"

#include "map.hpp"
#include "player.hpp"
#include "input_controller.hpp"
#include "camera.hpp"

void Game::start()
{
    init();
    loop();
}

Game::~Game()
{

    TTF_Quit();
    SDL_DestroyWindow(window);
}

void Game::init()
{
    initSDL();
    initAudio();
}

void Game::initSDL()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("SDL2 Window",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              0);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cout << "Failed to get create renderer\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        std::cout << "Failed to get open audio\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);

    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error:" << TTF_GetError() << std::endl;
        return;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return;
    }

    SDL_RenderSetLogicalSize(renderer, WINDOW_VIRTUAL_WIDTH, WINDOW_VIRTUAL_HEIGHT);

}

void Game::initAudio()
{
    Mix_Music *music = Mix_LoadMUS("sound/sample_mp3.mp3");
    Mix_PlayMusic(music, -1);
}

void Game::loop()
{

    int cameraX = 0, cameraY = 0, dCamera = 10;
    Map map{renderer};

    

    bool keepWindowOpen = true;

    InputController inputController;
    inputController.init();
    

    Player player(&inputController,renderer);
    player.transform.x = WINDOW_VIRTUAL_WIDTH/2+50;
    player.transform.y = WINDOW_VIRTUAL_HEIGHT/2+50;

    double dt;
    

    Camera camera{&player.transform, &map};

    Uint32 last = SDL_GetTicks();

    while (keepWindowOpen)
    {

        Uint32 start = SDL_GetTicks();
        dt = (start - last) / 1000.0;
        last = start;

        SDL_Event event;

        inputController.update();
        while (SDL_PollEvent(&event) > 0)
        {

            inputController.parseEvent(event);
            switch (event.type)
            {
            case SDL_QUIT:
                keepWindowOpen = false;
                break;
           
            }
        }

        player.update(dt);
        camera.update(dt);
     
        SDL_RenderClear(renderer);

        map.render(renderer, camera.getView());
        player.render(renderer,&camera);

        SDL_RenderPresent(renderer);

        Uint32 end = SDL_GetTicks();
        if (end - start < 30)
        {
            SDL_Delay(30 - (end - start));
        }


    }
}
