#include "animation.hpp"

#include <iostream>

// Animation::Animation(SDL_Texture *texture, std::vector<SDL_Rect> locations, int frameNumber, double frameRate, int xOffset, int yOffset)
// {
//     this->texture = texture;
//     this->locations = locations;
//     this->frameNumber = frameNumber;
//     this->frameRate = frameRate;
//     this->timeBetweenFrame = 1 / frameRate;
//     this->xOffset = xOffset;
//     this->yOffset = yOffset;
//     counter = 0.0;
// }

Animation::Animation(SDL_Texture *texture, int frameNumber, bool loop) : texture(texture), frameNumber(frameNumber), loop(loop)
{
    counter = 0.0;
    frames = new AnimationFrame[frameNumber];
}

void Animation::update(double dt)
{
    if ((!isRunning) || isEnded)
    {
        std::cout << "Not running or ended" << isRunning << " " << isEnded << std::endl;
        return;
    }

    counter += dt;

    if (counter > frames[currentIndex].frameDuration)
    {
        counter -= frames[currentIndex].frameDuration;
        currentIndex++;

        if (currentIndex >= frameNumber)
        {
            if (loop)
                currentIndex = 0;
            else
                isEnded = true;
        }
    }
}

void Animation::render(SDL_Renderer *renderer, Camera *camera, Transform *position)
{

    AnimationFrame &currentFrame = frames[currentIndex];

    SDL_Rect target = {position->ix() + currentFrame.xOffset, position->iy() + currentFrame.yOffset, currentFrame.source.w, currentFrame.source.h};

    SDL_RenderCopy(renderer, texture, &currentFrame.source, &target);
}

void Animation::start(bool restart)
{
    isRunning = true;
    if (restart)
        reset();
}

void Animation::pause()
{
    isRunning = false;
}

void Animation::reset()
{
    counter = 0.0;
    currentIndex = 0;
    isEnded = false;
}

void Animation::setFrame(int index, int x, int y, int w, int h, double frameDuration, int xOffset, int yOffset)
{
    frames[index].source = {x, y, w, h};
    frames[index].frameDuration = frameDuration;
    frames[index].xOffset = xOffset;
    frames[index].yOffset = yOffset;
}

bool Animation::hasEnded() const
{
    return isEnded;
}
