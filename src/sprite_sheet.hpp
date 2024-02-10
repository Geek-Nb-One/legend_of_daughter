#pragma once

#include <SDL2/SDL.h>

class SpriteSheet{

public:

    SpriteSheet(SDL_Renderer* renderer,const char* file,int width, int height, int tile_width, int tile_height);    

    void renderCopy(SDL_Renderer* renderer,int column, int row, int x , int y);
    void render(SDL_Renderer* renderer, int index, int x, int y );

    
private:
    int width, height, tile_width, tile_height;

    const int widthTileNumber;
    SDL_Texture* texture;

    void loadTexture(SDL_Renderer* renderer, const char* file);

    SDL_Rect locRect;
    SDL_Rect clipRect;
    

};