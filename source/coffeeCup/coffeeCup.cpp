#include "coffeeCup.h"

coffeeCup::coffeeCup(base *baseObj, bool direction,
    coffeeCup** coffeeCupArray, int coffeeCupArrayIndex)
{
    this->baseObj = baseObj;

    coffeeCupSize = vector2d(1314, 1322)/15;

    speed = 160.f;

    this->coffeeCupArray = coffeeCupArray;
    this->coffeeCupArrayIndex = coffeeCupArrayIndex;

    if(direction){
        screenLocation = dVector2d(baseObj->screenSize.X - coffeeCupSize.X, 0);
        this->direction = dVector2d(0, 0);
    }else{
        screenLocation = dVector2d(0, 0);
        this->direction = dVector2d(baseObj->screenSize.X, 0);
    }

    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/coffeeCup/coffeeCup.png");
    if(!texture){
        std::cout << "Error: could not create coffe cup texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
}

coffeeCup::~coffeeCup()
{
    if(texture){SDL_DestroyTexture(texture);}
    if(coffeeCupArray){
        coffeeCupArray[coffeeCupArrayIndex] = nullptr;
    }
}

void coffeeCup::tick()
{
    render();

    if(!screenLocation.inBox(dVector2d(0, 0), dVector2d(baseObj->screenSize.X, baseObj->screenSize.Y))){
        delete this;
        return;
    }

    screenLocation += (direction - screenLocation).norm() * baseObj->deltaTime * speed;
}

void coffeeCup::render()
{
    SDL_Rect rect = {(int)screenLocation.X, (int)screenLocation.Y, coffeeCupSize.X, coffeeCupSize.Y};
    SDL_RenderCopy(baseObj->mainRenderer, texture, NULL, &rect);
}
