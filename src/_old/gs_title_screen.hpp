#pragma once

#include "game_state.hpp"
#include <SDL2/SDL_ttf.h>

class gsTitleScreen : public GameState
{

public:

    gsTitleScreen(GameController *gameController, StateMachine *stateMachine, void (StateMachine::*changeStateHandle)(const std::string &));
    void init() override;
    void update(double dt) override;
    void render() override;
    void exit() override;

private:
    TTF_Font *ganonFont;
    SDL_Texture *splashTexture;
    SDL_Texture *titleTexture;
    SDL_Texture *titleShadowTexture;

    SDL_Rect titleScreenRect;
    SDL_Rect titleRect;
    SDL_Rect titleShadowRect;
};