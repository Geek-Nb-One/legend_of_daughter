#pragma once

#include "sprite_sheet.hpp"
#include "game_object.hpp"

class Animation
{
public:
    Animation(int frameNumber,double frameRate);

    void init(SpriteSheet * spriteSheet);
    void update(double dt);
    void render(SDL_Renderer* renderer,int x , int y);
private:

    double frameRate;
    double counter = 0.0;
    int currentIndex = 0;
    int frameNumber;

    SpriteSheet * spriteSheet;
};