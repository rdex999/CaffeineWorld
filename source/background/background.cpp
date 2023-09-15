#include "background.h"

background::background(base* baseObj)
{
    //store the baseObj pointer
    this->baseObj = baseObj;

    // load the image and create a surface
    SDL_Surface* tempSurface = IMG_Load("./images/background/backgroundMain.png");
    if(!tempSurface){
        std::cout << "Error: could not load background image.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    // create the background texture
    texture = SDL_CreateTextureFromSurface(baseObj->mainRenderer, tempSurface);
    if(!texture){
        std::cout << "Error: could not create background texture.\n" << SDL_GetError() << std::endl;
        exit(1); 
    }
    SDL_FreeSurface(tempSurface);

    baseObj->boxes.insert(baseObj->boxes.begin(), new box(texture, vector2d(0, 0), baseObj->screenSize, false, nullptr));
}

background::~background()
{
    if(texture){
        SDL_DestroyTexture(texture);
    }
}

void background::setBox()
{
    // insert a new box at the beginning of the array (index 0)
    baseObj->boxes[0] = new box(texture, vector2d(0, 0), baseObj->screenSize, false, nullptr);
}
