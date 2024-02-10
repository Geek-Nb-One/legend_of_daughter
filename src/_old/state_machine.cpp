#include "state_machine.hpp"


void StateMachine::update(double dt)
{
    currentState->update(dt);
}

void StateMachine::render()
{
    currentState->render();
}

void StateMachine::init(GameController *gameController)
{
    this->gameController = gameController;
}

void StateMachine::changeState(const std::string& nextStateKey)
{   
    
    if (currentState != nullptr){
        currentState->exit();
    }

    currentState = gameStateMap.at(nextStateKey);
    currentState->enter();

}
