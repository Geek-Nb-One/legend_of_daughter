#include "gs_title_screen.hpp"
#include "constant.hpp"

#include <iostream>

gsTitleScreen::gsTitleScreen(GameController *gameController, StateMachine *stateMachine, void (StateMachine::*changeStateHandle)(const std::string &))
: GameState(gameController,stateMachine,changeStateHandle){
}

void gsTitleScreen::init()
{

    SDL_Renderer * renderer = gameController->getRenderer();
    InputController &inputController = gameController->getInputController();
    inputController.reset();

    SDL_Surface* splashSurface = SDL_LoadBMP("graphics/splash_screen_base.bmp");

    if(!splashSurface){
        std::cout << "Failed to load splash Surface\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }
    splashTexture = SDL_CreateTextureFromSurface(renderer,splashSurface);
    
    ganonFont = TTF_OpenFont("font/retganon.ttf", 60);

    SDL_Color color = {255, 150, 150};
    SDL_Surface *surface = TTF_RenderText_Solid(ganonFont, "Legend of Daughter", color);
    titleTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Color colorShadow = {50, 50, 50};
    SDL_Surface *shadowSurface = TTF_RenderText_Solid(ganonFont, "Legend of Daughter", colorShadow);
    titleShadowTexture = SDL_CreateTextureFromSurface(renderer, shadowSurface);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(shadowSurface);
    SDL_FreeSurface(splashSurface);

    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(titleTexture, NULL, NULL, &texW, &texH);
    titleRect = {WINDOW_VIRTUAL_WIDTH / 2 - texW / 2, WINDOW_VIRTUAL_HEIGHT / 2 - texH / 2, texW, texH};
    titleShadowRect = {WINDOW_VIRTUAL_WIDTH / 2 - texW / 2 - 2, WINDOW_VIRTUAL_HEIGHT / 2 - texH / 2 + 1, texW, texH};
}

void gsTitleScreen::update(double dt)
{
    if (gameController->getInputController().isPressed(InputController::START)){
        changeState("game");
    }

}

void gsTitleScreen::render()
{   
    SDL_Renderer * renderer = gameController->getRenderer();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, splashTexture, NULL, NULL);
    SDL_RenderCopy(renderer, titleShadowTexture, NULL, &titleRect);
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleShadowRect);

    SDL_RenderPresent(renderer);
}


void gsTitleScreen::exit()
{
    SDL_DestroyTexture(splashTexture);
    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(titleShadowTexture);
}
