#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "game_controller.hpp"


class StateMachine;


class GameState
{
public:
    GameState(GameController * gameController,StateMachine* stateMachine, void (StateMachine::*changeStateHandle)(const std::string&));
    virtual void init();
    virtual void enter();
    virtual void update(double dt);
    virtual void render();
    virtual void exit();

    void changeState(const std::string& newState);

protected:
    GameController * gameController;
private:
    std::string nextState;
    void (StateMachine::* changeStateHandle)(const std::string&);
    StateMachine* stateMachine;

};