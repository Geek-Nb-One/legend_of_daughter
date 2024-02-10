#pragma once

#include <SDL2/SDL.h>
#include "sprite_sheet.hpp"

class Map{

public:

    Map(SDL_Renderer * renderer);

    void render(SDL_Renderer* renderer,const SDL_Rect& view);

    int getWidth()const;
    int getHeight() const;

private:
    SpriteSheet spriteSheet;
    int spriteIndex[96][54];
};