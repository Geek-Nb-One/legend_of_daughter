#include "game_state.hpp"

GameState::GameState(GameController *gameController, StateMachine *stateMachine, void (StateMachine::*changeStateHandle)(const std::string &))
    : gameController(gameController), stateMachine(stateMachine), changeStateHandle(changeStateHandle)
{
}

void GameState::init()
{
}

void GameState::enter()
{
}

void GameState::update(double dt)
{
}

void GameState::render()
{
}

void GameState::exit()
{
}

void GameState::changeState(const std::string &newState)
{
    (stateMachine->*changeStateHandle)(newState);
}
