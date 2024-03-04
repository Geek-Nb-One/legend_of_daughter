#pragma once

#include "sprite_sheet.hpp"
#include "game_object.hpp"
#include "animationFrame.hpp"
#include <vector>

class Animation
{
public:
    Animation(SDL_Texture* texture, int frameNumber,bool loop=false);
    void update(double dt);
    virtual void render(SDL_Renderer* renderer,Camera* camera,Transform* transform);

    void start(bool restart = false);
    void pause();
    void reset();

    void setFrame(int index,int x, int y, int w, int h, double frameDuration, int xOffset=0, int yOffset=0);

    bool hasEnded() const;
private:

    double counter = 0.0;
    int currentIndex = 0;
    int frameNumber;
    bool loop = false;
    bool isEnded = false;
    bool isRunning = false;


    SDL_Texture * texture;
    AnimationFrame* frames;


};