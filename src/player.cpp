#include "player.hpp"

#include <iostream>

const char *WALK_DOWN_IMAGE = "graphics/lili_top_front.png";
const char *WALK_RIGHT_IMAGE = "graphics/lili_walk_right.png";
const char *WALK_LEFT_IMAGE = "graphics/lili_walk_left.png";
const char *WALK_UP_IMAGE = "graphics/lili_walk_back.png";
const char *WALK_DOWN_LEFT_IMAGE = "graphics/lili_walk_down_left.png";
const char *WALK_DOWN_RIGHT_IMAGE = "graphics/lili_walk_down_right.png";
const char *WALK_UP_LEFT_IMAGE = "graphics/lili_walk_up_left.png";
const char *WALK_UP_RIGHT_IMAGE = "graphics/lili_walk_up_right.png";

const std::string WALK_RIGHT = "WALK_RIGHT";
const std::string WALK_LEFT = "WALK_LEFT";
const std::string WALK_DOWN = "WALK_DOWN";
const std::string WALK_UP = "WALK_UP";

const std::string WALK_DOWN_LEFT = "WALK_DOWN_LEFT";
const std::string WALK_DOWN_RIGHT = "WALK_DOWN_RIGHT";

const std::string WALK_UP_LEFT = "WALK_UP_LEFT";
const std::string WALK_UP_RIGHT = "WALK_UP_RIGHT";



Player::Player(InputController *inputController, SDL_Renderer *renderer) : inputController(inputController)
                                                                    
{

    addAnimation(renderer,WALK_DOWN_IMAGE, WALK_DOWN);
    addAnimation(renderer,WALK_RIGHT_IMAGE, WALK_RIGHT);
    addAnimation(renderer,WALK_LEFT_IMAGE, WALK_LEFT);
    addAnimation(renderer,WALK_UP_IMAGE, WALK_UP);
    addAnimation(renderer,WALK_DOWN_LEFT_IMAGE, WALK_DOWN_LEFT);
    addAnimation(renderer,WALK_DOWN_RIGHT_IMAGE, WALK_DOWN_RIGHT);
    addAnimation(renderer,WALK_UP_LEFT_IMAGE, WALK_UP_LEFT);
    addAnimation(renderer,WALK_UP_RIGHT_IMAGE, WALK_UP_RIGHT);

    currentAnimation = &animations.at(WALK_DOWN);
}

void Player::update(double dt)
{

    double dx = inputController->getX();
    double dy = inputController->getY();
    transform.x += dt * dx * speed;
    transform.y += dt * dy * speed;
    
    const double MOVE_TRESHOLD = 0.2;

    if (dx > MOVE_TRESHOLD)
    {
        if(dy > MOVE_TRESHOLD){
            currentAnimation = &animations.at(WALK_DOWN_RIGHT);
        }else if (dy < -MOVE_TRESHOLD){
             currentAnimation = &animations.at(WALK_UP_RIGHT);
        }else{
            currentAnimation = &animations.at(WALK_RIGHT);
        }  
    }
    else if (dx < -MOVE_TRESHOLD)
    {

         if(dy > MOVE_TRESHOLD){
            currentAnimation = &animations.at(WALK_DOWN_LEFT);
        }else if (dy < -MOVE_TRESHOLD){
             currentAnimation = &animations.at(WALK_UP_LEFT);
        }else{
            currentAnimation = &animations.at(WALK_LEFT);
        }  
 
    }
    else if (dy < -MOVE_TRESHOLD)
    {
        currentAnimation = &animations.at(WALK_UP);
    }
    else
    {
        currentAnimation = &animations.at(WALK_DOWN);
    }

    currentAnimation->update(dt);
}

void Player::render(SDL_Renderer *renderer, Camera *camera)
{
    SDL_Rect rect = camera->getScreenRect(transform.ix() - 8, transform.iy() - 16);
    // Uint8 r,g,b,a;
    // SDL_GetRenderDrawColor(renderer,&r,&g,&b,&a);
    // SDL_SetRenderDrawColor(renderer,255,0,0,255);

    //
    // rect.w = 16;
    // rect.h = 32;
    // SDL_RenderDrawRect(renderer,&rect);

    // SDL_SetRenderDrawColor(renderer,r,g,b,a);

    currentAnimation->render(renderer, rect.x, rect.y);
}



void Player::addAnimation(SDL_Renderer *renderer, const char *file, std::string name)
{
    spriteSheets.insert(make_pair(name, SpriteSheet{renderer, file, 64, 32, 16, 32}));
    animations.insert(make_pair(name, Animation{4, 4}));
    animations.at(name).init(&(spriteSheets.at(name)));
}
