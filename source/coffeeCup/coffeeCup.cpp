#include "coffeeCup.h"

coffeeCup::coffeeCup(base *baseObj)
{
    this->baseObj = baseObj;

    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/coffeeCup/coffeeCup.png");
    if(!texture){
        std::cout << "Error: could not create coffe cup texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    boxPtr = new box(std::bind(&coffeeCup::tick, this, std::placeholders::_1));
    baseObj->boxes.insert(baseObj->boxes.end(), boxPtr);
}

coffeeCup::~coffeeCup()
{
    if(texture){SDL_DestroyTexture(texture);}
}

void coffeeCup::tick(double deltaTime)
{
    render();
}

void coffeeCup::render()
{
    SDL_Rect rect = {(int)screenLocation.X, (int)screenLocation.Y, coffeeCupSize.X, coffeeCupSize.Y};
    SDL_RenderCopy(baseObj->mainRenderer, texture, NULL, &rect);
}
