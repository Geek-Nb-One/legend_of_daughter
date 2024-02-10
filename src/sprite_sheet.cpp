#include "sprite_sheet.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

SpriteSheet::SpriteSheet(SDL_Renderer *renderer, const char *file, int width, int height, int tile_width, int tile_height) : width(width), height(height), tile_width(tile_width), tile_height(tile_height), widthTileNumber(width / tile_width)
{
    loadTexture(renderer, file);

    locRect.w = tile_width;
    locRect.h = tile_height;

    clipRect.w = tile_width;
    clipRect.h = tile_height;

}

void SpriteSheet::renderCopy(SDL_Renderer *renderer,  int column, int row, int x , int y)
{
    
    locRect.x = x;
    locRect.y = y;

    clipRect.x = column * tile_width;
    clipRect.y = row * tile_height;


    SDL_RenderCopy( renderer, texture,&clipRect, &locRect );
}

void SpriteSheet::render(SDL_Renderer* renderer, int index, int x, int y)
{
    renderCopy(renderer, index%widthTileNumber, index /widthTileNumber,x,y);
}


void SpriteSheet::loadTexture(SDL_Renderer *renderer, const char *file)
{
    SDL_Surface *surface;

    surface = IMG_Load(file);
    if (surface == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", file, IMG_GetError());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", file, SDL_GetError());
        }

        SDL_FreeSurface(surface);
    }
}

