#include "camera.hpp"
#include "constant.hpp"

#include <iostream>

Camera::Camera(Transform *transform, Map *map) : transform(transform), map(map)
{
    view.w = WINDOW_VIRTUAL_WIDTH;
    view.h = WINDOW_VIRTUAL_HEIGHT;
}

void Camera::init()
{
}

int getBoundedCoord(int value, int mapBound, int cameraBound){
    if (value - cameraBound < 0 ){
        return 0;
    }else if (value + cameraBound >= mapBound){
        return mapBound - cameraBound * 2 -1;
    }else{
        return value - cameraBound;
    }
}


void Camera::update(double dt)
{

    view.x = getBoundedCoord(transform->x,map->getWidth(),view.w/2);
    view.y = getBoundedCoord(transform->y,map->getHeight(),view.h/2);

}

void Camera::render(SDL_Renderer* renderer,SDL_Texture *texture, const SDL_Rect *crop,Transform * position)
{
    if(objectIsInBound(position->x,position->y)){
        int screenX = position->x - view.x;
        int screenY = position->y - view.y;
        SDL_Rect loc{screenX,screenY, crop->w,crop->h};
        SDL_RenderCopy(renderer,texture,crop,&loc);
    }
}

SDL_Rect Camera::getScreenRect(int x, int y) const
{
    return {x - view.x,y- view.y};
}

const SDL_Rect &Camera::getView() const
{
    return view;
}

bool Camera::objectIsInBound(int x, int y) const
{
    x-= view.x;
    y -= view.y;
    return ( x >= 0 &&  y >= 0 && x <= view.w && y <= view.h );
}
