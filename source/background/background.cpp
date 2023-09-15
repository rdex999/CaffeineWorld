#include "background.h"

background::background(base* baseObj)
{
    SDL_Surface* tempSurface = IMG_Load("./images/background.png");
    if(!tempSurface){
        std::cout << "Error: could not load background image. " << SDL_GetError() << std::endl;
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(baseObj->mainRenderer, tempSurface);
    if(!texture){
        std::cout << "Error: could not create background texture." << std::endl;
        exit(1); 
    }
    SDL_FreeSurface(tempSurface);

    // insert the background texture to the boxes array at index 0
    baseObj->boxes.insert(baseObj->boxes.begin(), new box(texture, vector2d(0, 0), baseObj->screenSize)); 
}

background::~background()
{
    if(texture){
        SDL_DestroyTexture(texture);
    }
}