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

SDL_Rect Camera::getScreenRect(int x, int y) const
{
    return {x - view.x,y- view.y};
}

const SDL_Rect &Camera::getView() const
{
    return view;
}
