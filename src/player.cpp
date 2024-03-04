#include "player.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
Player::Player(InputController *inputController, SDL_Renderer *renderer) : inputController(inputController)

{
    loadTexture(renderer, "graphics/world_of_solaria/Old/32x32/Heroes/Hero 02a 32.png","graphics/world_of_solaria/Old/32x32/Weapons/Sword 01-32.png");

    initAnim(0, Direction::Down);
    initAnim(1, Direction::Left);
    initAnim(2, Direction::Right);
    initAnim(3, Direction::Top);

    currentAnimation = &animations.at(std::make_pair(direction, action));
    currentAnimation->start(true);
}

void Player::update(double dt)
{

    currentAnimation->update(dt);

    Direction currentDirection = direction;
    Action currentAction = action;

    for(auto b: buffer){
        b.timer += dt;
    }

    bool bufferSearch = !buffer.empty();

    while(bufferSearch){
        if (buffer.front().timer > bufferDuration){
            buffer.pop_front();
            bufferSearch = !buffer.empty();
        }else{
            bufferSearch = false;
        }

    }


    if (action == Action::Attack)
    {

        if(currentAnimation->hasEnded())
            currentAction = Action::Idle;

        if(inputController->getAttackState() == InputController::ActionState::Down && buffer.size() < bufferLength){
            buffer.emplace_back(Command(Action::Attack));
        }
    }
    else
    {

        if(!buffer.empty()){
            currentAction = buffer.front().action;
            buffer.pop_front();
        }
        else if (inputController->getAttackState() == InputController::ActionState::Down)
        {
            currentAction = Action::Attack;

        }
        else
        {
            double dx = inputController->getX();
            double dy = inputController->getY();

            const double MOVE_TRESHOLD = 0.2;

            if (abs(dx) > abs(dy) && abs(dx) > MOVE_TRESHOLD)
            {
                transform.x += dt * dx * speed;
                currentDirection = dx > 0 ? Direction::Right : Direction::Left;
                isMoving = true;
            }
            else if (abs(dy) > MOVE_TRESHOLD)
            {
                transform.y += dt * dy * speed;
                currentDirection = dy > 0 ? Direction::Down : Direction::Top;
                isMoving = true;
            }
            else
            {
                currentDirection = direction;
                isMoving = false;
            }

            currentAction = isMoving ? Action::Walk : Action::Idle;
        }
    }

    bool changeAnim = false;
    if (direction != currentDirection)
    {
        changeAnim = true;
        direction = currentDirection;
    }

    if (action != currentAction)
    {
        changeAnim = true;
        action = currentAction;
    }

    if (changeAnim)
    {
        currentAnimation = &animations.at(std::make_pair(direction, action));
        currentAnimation->start(true);
    }


}

void Player::render(SDL_Renderer *renderer, Camera *camera)
{

    currentAnimation->render(renderer, camera, &transform);
}

void Player::loadTexture(SDL_Renderer *renderer, const char *file,const char* weapon)
{

    
    SDL_Surface *surface;
    SDL_Texture *charTexture , *weaponTexture;
    surface = IMG_Load(file);
    if (surface == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", file, IMG_GetError());
    }
    else
    {
        charTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (charTexture == nullptr)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", file, SDL_GetError());
        }

        SDL_FreeSurface(surface);
    }

    surface = IMG_Load(weapon);
    if (surface == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", weapon, IMG_GetError());
    }
    else
    {
        weaponTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (weaponTexture == nullptr)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", weapon, SDL_GetError());
        }

        SDL_FreeSurface(surface);
    }
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 256, 512);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_Rect rect{0,0,256,512};

    SDL_SetRenderTarget(renderer,texture);
    SDL_RenderCopy(renderer,charTexture,NULL,NULL);
    SDL_RenderCopy(renderer,weaponTexture,NULL,NULL);

    SDL_SetRenderTarget(renderer,NULL);

}

void Player::initAnim(int index, Direction direction)
{

    double duration = 1.0 / 8.0;
    double attack_duration = 1.0/16.0;

    auto idle = std::make_pair(direction, Action::Idle);
    auto walk = std::make_pair(direction, Action::Walk);
    auto attack = std::make_pair(direction, Action::Attack);

    animations.insert(std::make_pair(idle, Animation(texture, 4,true)));
    animations.insert(std::make_pair(walk, Animation(texture, 4,true)));
    animations.insert(std::make_pair(attack, Animation(texture, 4,false)));

    for (int i = 0; i < 4; i++)
    {
        animations.at(idle).setFrame(i, i * 32, index * 32, 32, 32, duration);
        animations.at(walk).setFrame(i, i * 32, (index + 4) * 32, 32, 32, duration);
    }
    switch (direction)
    {
    case Direction::Down:
        animations.at(attack).setFrame(0, 0, 256, 64, 64, attack_duration, -32);
        animations.at(attack).setFrame(1, 64, 256, 64, 64, attack_duration, -32);
        animations.at(attack).setFrame(2, 128, 256, 64, 64, attack_duration);
        animations.at(attack).setFrame(3, 192, 256, 64, 64, attack_duration);
        break;
    case Direction::Top:
        animations.at(attack).setFrame(0, 0, 320, 64, 64, attack_duration,0,-32);
        animations.at(attack).setFrame(1, 64, 320, 64, 64, attack_duration,0,-32);
        animations.at(attack).setFrame(2, 128, 320, 64, 64, attack_duration,-32,-32);
        animations.at(attack).setFrame(3, 192, 320, 64, 64, attack_duration,-32,-32);
        break;
    case Direction::Right:
        animations.at(attack).setFrame(0, 0, 384, 64, 64, attack_duration);
        animations.at(attack).setFrame(1, 64, 384, 64, 64, attack_duration);
        animations.at(attack).setFrame(2, 128, 384, 64, 64, attack_duration,0,-32);
        animations.at(attack).setFrame(3, 192, 384, 64, 64, attack_duration,0,-32);
        break;
    case Direction::Left:
        animations.at(attack).setFrame(0, 0, 448, 64, 64, attack_duration,-32,-32);
        animations.at(attack).setFrame(1, 64, 448, 64, 64, attack_duration,-32,-32);
        animations.at(attack).setFrame(2, 128, 448, 64, 64, attack_duration,-32);
        animations.at(attack).setFrame(3, 192, 448, 64, 64, attack_duration,-32);
        break;
    }
}
