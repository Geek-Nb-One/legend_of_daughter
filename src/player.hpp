#pragma once

#include "game_object.hpp"
#include "input_controller.hpp"
#include "animation.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>


class Player: public GameObject{

public:
    Player(InputController * inputController,SDL_Renderer * renderer);

    void update(double dt) override;
    void render(SDL_Renderer * renderer,Camera* camera) override;
private:

    int speed = 200;
    InputController * inputController;


    std::map<std::string,Animation> animations;
    std::map<std::string, SpriteSheet> spriteSheets;

    // Animation  walkFrontAnimation{4,4};
    // Animation walkRightAnimation{4,4};
    // Animation walkLeftAnimation{4,4};
    // Animation walkBackAnimation{4,4};

    // SpriteSheet walkFrontSheet;
    // SpriteSheet walkRightSheet;
    // SpriteSheet walkLeftSheet;
    // SpriteSheet walkBackSheet;

    Animation * currentAnimation;

    void addAnimation(SDL_Renderer* renderer,const char* file,std::string name);

};