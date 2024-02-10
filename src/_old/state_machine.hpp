#pragma once

#include <string>
#include <map>
#include "game_state.hpp"
#include "game_controller.hpp"

class StateMachine
{

public:

    void init(GameController* gameController);

    template <class T>
    void addState(std::string stateKey);
    
    void changeState(const std::string& newState);

    void update(double dt);
    void render();

private:


    std::string currentStateKey;
    std::string nextStateKey;
    GameController* gameController =nullptr;
    GameState* currentState =nullptr;
    std::map<std::string,GameState* > gameStateMap;
    
};


template <class T>
void StateMachine::addState(std::string stateKey)
{
    GameState * newState = new T(this->gameController,this,&(StateMachine::changeState));
    newState->init();
    gameStateMap.insert({stateKey,newState});

}


