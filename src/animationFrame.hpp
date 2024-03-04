#pragma once
#include <SDL2/SDL.h>

struct AnimationFrame
{
    SDL_Rect source{0, 0, 0, 0};
    int xOffset = 0;
    int yOffset = 0;
    double frameDuration=0.1;

   
};