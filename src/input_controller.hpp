#pragma once

#include <SDL2/SDL.h>
#include <map>

class InputController
{
private:
    const int CONTROLLER_DEAD_ZONE = 8000;
    const int UP_KEY = 0;
    const int DOWN_KEY = 1;
    const int LEFT_KEY = 2;
    const int RIGHT_KEY = 3;

    const int UP_DIR = 1;
    const int DOWN_DIR = 2;
    const int LEFT_DIR = 4;
    const int RIGHT_DIR = 8;



public:
    enum ActionState
    {
        Free,
        Down,
        Pressed,
        Up
    };

    void init();
    void update();
    void exit();

    void parseEvent(SDL_Event &event);



    bool getIsControllerActive() const;

    double getX() const;
    double getY() const;

    ActionState getAttackState() const;
    ActionState getRollState() const;

private:
    SDL_GameController *gameController = nullptr;
    bool isControllerActive = false;

    void parseControllerButtonDown(SDL_Event &event);
    void parseControllerButtonUp(SDL_Event &event);
    void parseControllerAxisMotion(SDL_Event &event);
    void parseKeyboardDown(SDL_Event &event);
    void parseKeyboardUp(SDL_Event &event);

    void setDirectionFromKey();


    ActionState attackState = ActionState::Free;
    ActionState rollState = ActionState::Free;
    ActionState startState = ActionState::Free;

    int dirKeyPressed =0;


    double x = 0.0, y = 0.0;
};
