#include "bullet.h"

bullet::bullet(base *baseObj, std::vector<box*>::iterator boxesIterator,
    vector2d &shootFromTo, vector2d &shootTo, bool flip)
{
    this->baseObj = baseObj;

    size = vector2d(1550, 260)/15;

    this->shootFrom = shootFrom;
    this->shootTo = shootTo;

    rotation = baseObj->rotationPlayerToMouse;

    this->flip = flip;

    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/bullet/bullet.png");
    if(!texture){
        std::cout << "Error: could not create bullet texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    boxPtr = new box(std::bind(&bullet::render, this),
        std::bind(&bullet::tick, this, std::placeholders::_1));

    baseObj->boxes.insert(boxesIterator, boxPtr);

}

bullet::~bullet()
{
    if(texture){SDL_DestroyTexture(texture);}
    
    baseObj->boxes.erase(boxesIterator);

    if(baseObj->boxes[std::distance(baseObj->boxes.begin(), boxesIterator)]){
        delete baseObj->boxes[std::distance(baseObj->boxes.begin(), boxesIterator)];
    }
}

void bullet::tick(double deltaTime)
{
    shootFrom = vector2d(shootTo.X - shootFrom.X, shootTo.Y - shootFrom.Y).norm();
    if(!shootFrom.inBox(vector2d(0, 0), baseObj->screenSize)){
        this->~bullet();
    }
    shootFrom.printVec();
}

void bullet::render()
{
    SDL_Rect rect = {shootFrom.X, shootFrom.Y, size.X, size.Y};
    SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &rect, rotation, NULL, SDL_RendererFlip(flip));
}