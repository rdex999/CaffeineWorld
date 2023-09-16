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
    // update the box at the beginning of the array (index 0)
    baseObj->boxes[1]->texture = texture;
}
