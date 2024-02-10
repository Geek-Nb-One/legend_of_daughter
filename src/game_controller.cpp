#include "game_controller.hpp"



void GameController::init(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    inputController.init();
}

void GameController::parseEvent()
{
    inputController.reset();

  
}

InputController &GameController::getInputController()
{
    return inputController;
}

SDL_Renderer *GameController::getRenderer()
{
    return renderer;
}

bool GameController::getKeepWindowOpen() const
{
    return keepWindowOpen;
}
