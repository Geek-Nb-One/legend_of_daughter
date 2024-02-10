#include "animation.hpp"

Animation::Animation( int frameNumber,double frameRate):frameNumber(frameNumber), frameRate(frameRate)
{
}

void Animation::init(SpriteSheet *spriteSheet)
{
    this->spriteSheet = spriteSheet;
}

void Animation::update(double dt)
{
    counter += dt;

    if (counter > 1/ frameRate){
        counter -= 1/frameRate;
        currentIndex = (currentIndex + 1)% frameNumber;
    }
}

void Animation::render(SDL_Renderer *renderer,int x, int y)
{
    spriteSheet->render(renderer,currentIndex,x,y);
}
