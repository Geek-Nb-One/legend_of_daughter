#pragma once


class GameController{
public:

    void init(SDL_Renderer * getRenderer);
    void parseEvent();


    SDL_Renderer * getRenderer();


    bool getKeepWindowOpen() const;


private:

    InputController inputController;
    SDL_Renderer * renderer;

    bool keepWindowOpen = true;




};