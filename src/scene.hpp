#pragma once

#include <vector>
#include "game_object.hpp"

class Scene{

public:
    void addGameObject(GameObject* gameObject);
    void update(double dt);
    void render(SDL_Renderer* renderer);

private:

    std::vector<GameObject*> gameObjects;
    void sortGameObjects();
};