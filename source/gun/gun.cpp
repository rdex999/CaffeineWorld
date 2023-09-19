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

    box* tempBoxPtr = new box(texture,
        playerObj->screenLocation, vector2d(251, 130)/2, true,
        std::bind(&gun::tick, this, std::placeholders::_1), playerObj->flip);

    baseObj->boxes.insert(baseObj->boxes.end() - (inventoryObj->firstBoxIndex), tempBoxPtr);

    boxesIndex = std::distance(baseObj->boxes.begin(), std::find(baseObj->boxes.begin(), baseObj->boxes.end(), tempBoxPtr));
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
    baseObj->boxes[boxesIndex]->startPosition = playerObj->screenLocation;
    baseObj->boxes[boxesIndex]->startPosition.Y = playerObj->screenLocation.Y + playerObj->playerSize.Y/2.3;
    baseObj->boxes[boxesIndex]->flip = playerObj->flip;
}
