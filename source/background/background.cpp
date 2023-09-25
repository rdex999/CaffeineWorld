#include "background.h"

background::background(base* baseObj)
{
    //store the baseObj pointer
    this->baseObj = baseObj;

    // load the image and create a surface
    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/background/backgroundMain.png");
    if(!texture){
        std::cout << "Error: could not create background texture.\n" << SDL_GetError() << std::endl;
        exit(1); 
    }

    baseObj->boxes.insert(baseObj->boxes.end(), new box(std::bind(&background::render, this)));
}

background::~background()
{
    if(texture){
        SDL_DestroyTexture(texture);
    }
}

void background::render()
{
    SDL_Rect rect = {0, 0, baseObj->screenSize.X, baseObj->screenSize.Y};
    SDL_RenderCopy(baseObj->mainRenderer, texture, NULL, &rect);
}