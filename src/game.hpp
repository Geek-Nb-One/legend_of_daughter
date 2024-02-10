#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Game{
public:
    Game() = default;
    ~Game();
    void start();
    
private:
    void init();
    void initSDL();
    void initAudio();
    void initGameController();
    void loop();

    SDL_Window* window;
    SDL_Renderer * renderer;

};