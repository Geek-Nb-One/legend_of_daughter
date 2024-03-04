#pragma once

#include "game_object.hpp"
#include "input_controller.hpp"
#include "animation.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <deque>

class Player : public GameObject
{

public:
    Player(InputController *inputController, SDL_Renderer *renderer);

    void update(double dt) override;
    void render(SDL_Renderer *renderer, Camera *camera) override;

    void loadTexture(SDL_Renderer *renderer, const char *file, const char* weapon);

private:
    int speed = 200;
    bool isMoving = false;

    double bufferTimer = 0.0;
    Action actionBuffer;

    Direction direction = Direction::Down;
    Action action = Action::Idle;
    InputController *inputController;

    std::map<std::pair<Direction, Action>, Animation> animations;

    Animation *currentAnimation;
    SDL_Texture *texture;

    void initAnim(int index, Direction direction);

    struct Command
    {
        Action action;
        double timer=0.0;

        Command (Action action): action(action){}
    };

    std::deque<Command> buffer;
    int bufferLength = 1;
    double bufferDuration = 1.0;
};