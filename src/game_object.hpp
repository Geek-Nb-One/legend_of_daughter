#pragma once

#include <SDL2/SDL.h>
#include "transform.hpp"
#include "camera.hpp"

class GameObject
{
public:
    virtual void update(double dt);
    virtual void render(SDL_Renderer * renderer,Camera* camera);

    bool operator<(const GameObject &other) const;

    Transform transform;
  

};