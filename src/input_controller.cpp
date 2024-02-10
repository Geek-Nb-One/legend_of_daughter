#include "input_controller.hpp"

#include <iostream>
#include <math.h>

void InputController::init()
{
    if (SDL_NumJoysticks() > 0)
    {
        std::cout << "Game Controller connected" << std::endl;
        gameController = SDL_GameControllerOpen(0);
        isControllerActive = true;
    }
}

void InputController::parseEvent(SDL_Event &event)
{

    if (isControllerActive)
    {
        if (event.type == SDL_CONTROLLERBUTTONDOWN)
            parseControllerButtonDown(event);
        else if (event.type == SDL_CONTROLLERBUTTONUP)
            parseControllerButtonUp(event);
        else if (event.type == SDL_CONTROLLERAXISMOTION)
            parseControllerAxisMotion(event);
    }
    else
    {
        if (event.type == SDL_KEYDOWN)
            parseKeyboardDown(event);
        else if (event.type == SDL_KEYUP)
            parseKeyboardUp(event);
    }
}

void InputController::parseControllerAxisMotion(SDL_Event &event)
{

    switch (event.caxis.axis)
    {
    case SDL_CONTROLLER_AXIS_LEFTX:

        if (event.caxis.value > CONTROLLER_DEAD_ZONE)
        {
            x = event.caxis.value / 32767.0;
        }
        else if (event.caxis.value < -CONTROLLER_DEAD_ZONE)
        {
            x = event.caxis.value / 32768.0;
        }
        else
        {
            x = 0.0;
        }

        break;
    case SDL_CONTROLLER_AXIS_LEFTY:
        if (event.caxis.value > CONTROLLER_DEAD_ZONE)
        {
            y = event.caxis.value / 32767.0;
        }
        else if (event.caxis.value < -CONTROLLER_DEAD_ZONE)
        {
            y = event.caxis.value / 32768.0;
        }
        else
        {
            y = 0.0;
        }
        break;
    }
}

void InputController::parseControllerButtonDown(SDL_Event &event)
{

    switch (event.cbutton.button)
    {
    case SDL_CONTROLLER_BUTTON_A:
        attackState = ActionState::Down;
        break;
    case SDL_CONTROLLER_BUTTON_B:
        rollState = ActionState::Down;
        break;
    case SDL_CONTROLLER_BUTTON_X:

        break;

    case SDL_CONTROLLER_BUTTON_Y:

        break;

    case SDL_CONTROLLER_BUTTON_GUIDE:

        break;
    case SDL_CONTROLLER_BUTTON_START:
        startState = ActionState::Down;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:

        break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:

        break;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:

        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:

        break;
    case SDL_CONTROLLER_BUTTON_BACK:

        break;
    default:

        break;
    }
}

void InputController::parseControllerButtonUp(SDL_Event &event)
{
    switch (event.cbutton.button)
    {
    case SDL_CONTROLLER_BUTTON_A:
        attackState = ActionState::Up;
        break;
    case SDL_CONTROLLER_BUTTON_B:
        rollState = ActionState::Up;
        break;
    case SDL_CONTROLLER_BUTTON_START:
        startState = ActionState::Up;
        break;
    }
}

void InputController::parseKeyboardDown(SDL_Event &event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        dirKeyPressed |= UP_DIR;
        setDirectionFromKey();
        break;
    case SDLK_DOWN:
        dirKeyPressed |= DOWN_DIR;
        setDirectionFromKey();
        break;
    case SDLK_RIGHT:
        dirKeyPressed |= RIGHT_DIR;
        setDirectionFromKey();
        break;
    case SDLK_LEFT:
        dirKeyPressed |= LEFT_DIR;
        setDirectionFromKey();
        break;
    case SDLK_w:
        dirKeyPressed |= UP_DIR;
        setDirectionFromKey();
        break;
    case SDLK_s:
        dirKeyPressed |= DOWN_DIR;
        setDirectionFromKey();
        break;
    case SDLK_d:
        dirKeyPressed |= RIGHT_DIR;
        setDirectionFromKey();
        break;
    case SDLK_a:
        dirKeyPressed |= LEFT_DIR;
        setDirectionFromKey();
        break;
    }
}

void InputController::parseKeyboardUp(SDL_Event &event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        dirKeyPressed &= (~UP_DIR);
        setDirectionFromKey();
        break;
    case SDLK_DOWN:
        dirKeyPressed &= (~DOWN_DIR);
        setDirectionFromKey();
        break;
    case SDLK_RIGHT:
        dirKeyPressed &= (~RIGHT_DIR);
        setDirectionFromKey();
        break;
    case SDLK_LEFT:
        dirKeyPressed &= (~LEFT_DIR);
        setDirectionFromKey();
        break;
    case SDLK_w:
        dirKeyPressed &= (~UP_DIR);
        setDirectionFromKey();
        break;
    case SDLK_s:
        dirKeyPressed &= (~DOWN_DIR);
        setDirectionFromKey();
        break;
    case SDLK_d:
        dirKeyPressed &= (~RIGHT_DIR);
        setDirectionFromKey();
        break;
    case SDLK_a:
        dirKeyPressed &= (~LEFT_DIR);
        setDirectionFromKey();
        break;
    }
}

void InputController::setDirectionFromKey()
{
    if (dirKeyPressed == UP_DIR)
    {
        x = 0.0;
        y = -1.0;
    }
    else if (dirKeyPressed == DOWN_DIR)
    {
        x = 0.0;
        y = 1.0;
    }
    else if (dirKeyPressed == LEFT_DIR)
    {
        x = -1.0;
        y = 0.0;
    }
    else if (dirKeyPressed == RIGHT_DIR)
    {
        x = 1.0;
        y = 0.0;
    }
    else if (dirKeyPressed == UP_DIR + LEFT_DIR)
    {
        x = -sqrt(2);
        y = -sqrt(2);
    }
    else if (dirKeyPressed == UP_DIR + RIGHT_DIR)
    {
        x = sqrt(2);
        y = -sqrt(2);
    }
    else if (dirKeyPressed == DOWN_DIR + LEFT_DIR)
    {
        x = -sqrt(2);
        y = sqrt(2);
    }
    else if (dirKeyPressed == DOWN_DIR + RIGHT_DIR)
    {
        x = sqrt(2);
        y = sqrt(2);
    }
}

void updateState(InputController::ActionState &action)
{
    if (action == InputController::ActionState::Down)
        action = InputController::ActionState::Pressed;
    if (action == InputController::ActionState::Up)
        action = InputController::ActionState::Free;
}

void InputController::update()
{
    updateState(attackState);
    updateState(rollState);
    updateState(startState);
}

void InputController::exit()
{
    SDL_GameControllerClose(gameController);
}

bool InputController::getIsControllerActive() const
{
    return isControllerActive;
}

double InputController::getX() const
{
    return x;
}

double InputController::getY() const
{
    return y;
}

InputController::ActionState InputController::getAttackState() const
{
    return attackState;
}

InputController::ActionState InputController::getRollState() const
{
    return rollState;
}
