#include "scene.hpp"
#include <algorithm>

bool comparePtrToNode(GameObject *a, GameObject *b) { return (*a < *b); }

void Scene::addGameObject(GameObject *gameObject)
{
    gameObjects.emplace_back(gameObjects);
}

void Scene::update(double dt)
{

    for (auto &go : gameObjects)
    {
        go->update(dt);
    }
}

void Scene::render(SDL_Renderer *renderer)
{

    sortGameObjects();

    for (auto &go : gameObjects)
    {
        go->render(renderer);
    }
}

void Scene::sortGameObjects()
{
    std::sort(gameObjects.begin(), gameObjects.end(), comparePtrToNode);
}
