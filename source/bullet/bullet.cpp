#include "bullet.h"

bullet::bullet(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/bullet/bullet.png");
    if(!texture){
        std::cout << "Error: could not create bullet texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
}

bullet::~bullet()
{
    if(texture){SDL_DestroyTexture(texture);}
}

void bullet::render()
{

}

void bullet::tick(double deltaTime)
{

}