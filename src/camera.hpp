#pragma once

#include "map.hpp"
#include "transform.hpp"

#include <SDL2/SDL.h>

class Camera{

public:

    Camera(Transform* transform, Map* map);

    void init();
    void update(double dt);

    void render(SDL_Renderer* renderer,SDL_Texture* texture, const SDL_Rect* crop, Transform* position);
    SDL_Rect getScreenRect(int x, int y) const;

    const SDL_Rect& getView() const;

private:
    Transform* transform;
    Map* map;

    SDL_Rect view;


    bool objectIsInBound(int x, int y)const;


};