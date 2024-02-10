#include "game_object.hpp"

void GameObject::update(double dt)
{
}

void GameObject::render(SDL_Renderer * renderer, Camera *camera)
{
}

bool GameObject::operator<(const GameObject &other) const
{
    return this->transform < other.transform;
}


