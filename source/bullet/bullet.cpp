#include "bullet.h"

bullet::bullet(base *baseObj, std::vector<box*>::iterator boxesIterator,
    vector2d *shootFrom, bool flip)
{
    this->baseObj = baseObj;

    size = vector2d(1550, 260)/20;

    this->shootFrom = dVector2d(shootFrom->X, shootFrom->Y);

    rotation = baseObj->rotationPlayerToMouse * (M_PI/180.f);

    this->flip = flip;

    speed = 70.f;

    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/bullet/bullet.png");
    if(!texture){
        std::cout << "Error: could not create bullet texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    boxPtr = new box(std::bind(&bullet::tick, this, std::placeholders::_1));

    baseObj->boxes.insert(boxesIterator, boxPtr);

}

bullet::~bullet()
{
    std::cout << "Destroying bullet" << std::endl;
    if(texture){SDL_DestroyTexture(texture);}
    
    baseObj->boxes.erase(std::find(baseObj->boxes.begin(), baseObj->boxes.end(), boxPtr));

    if(boxPtr){
        delete boxPtr;
    }
}

void bullet::tick(double deltaTime)
{
    render();

    if(flip){
        shootFrom += dVector2d(std::cos(rotation) * deltaTime * speed * 15, std::sin(rotation) * deltaTime * speed * 15);
    }else{
        shootFrom -= dVector2d(std::cos(rotation) * deltaTime * speed * 15, std::sin(rotation) * deltaTime * speed * 15);
    } 
    if(!shootFrom.inBox(dVector2d(0, 0), dVector2d(baseObj->screenSize.X, baseObj->screenSize.Y))){
        delete this;
    }
}

void bullet::render()
{
    SDL_Rect rect = {(int)shootFrom.X, (int)shootFrom.Y, size.X, size.Y};
    SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &rect, rotation * (180/M_PI), NULL, SDL_RendererFlip(flip));
}