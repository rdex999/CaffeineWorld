#include "gun.h"

gun::gun(base *baseObj, player *playerObj, inventory* inventoryObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->inventoryObj = inventoryObj;

    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/gun/gun.png");
    if(!texture){
        std::cout << "Error: could not load gun texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    boxPtr = new box(texture,
        playerObj->screenLocation, vector2d(251, 130)/2, true,
        std::bind(&gun::tick, this, std::placeholders::_1), playerObj->flip);

    baseObj->boxes.insert(baseObj->boxes.end() - (inventoryObj->firstBoxIndex), boxPtr);
}

gun::~gun()
{
    if(texture){SDL_DestroyTexture(texture);}
}

void gun::tick(double deltaTime)
{
    setBox();
}

void gun::setBox()
{
    boxPtr->startPosition = playerObj->screenLocation;
    boxPtr->flip = playerObj->flip;
}
