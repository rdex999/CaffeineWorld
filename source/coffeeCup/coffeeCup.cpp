#include "coffeeCup.h"

coffeeCup::coffeeCup(base *baseObj, bool direction, SDL_Texture* texture,
    coffeeCup** coffeeCupArray, int coffeeCupArrayIndex)
{
    this->baseObj = baseObj;

    coffeeCupSize = vector2d(1314, 1322)/15;

    speed = 160.f;

    this->coffeeCupArray = coffeeCupArray;
    this->coffeeCupArrayIndex = coffeeCupArrayIndex;

    this->texture = texture;

    if(direction){
        screenLocation = dVector2d(baseObj->screenSize.X - coffeeCupSize.X, 20);
        this->direction = dVector2d(0, 20);
    }else{
        screenLocation = dVector2d(0, 20);
        this->direction = dVector2d(baseObj->screenSize.X, 20);
    }

    runningTime = 0;
}

coffeeCup::~coffeeCup()
{
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
    
    runningTime += baseObj->deltaTime;
    screenLocation.X += ((direction - screenLocation).norm() * baseObj->deltaTime * speed).X;
    screenLocation.Y += 2.3 * std::sin(runningTime*5);
}

void coffeeCup::render()
{
    SDL_Rect rect = {(int)screenLocation.X, (int)screenLocation.Y, coffeeCupSize.X, coffeeCupSize.Y};
    SDL_RenderCopy(baseObj->mainRenderer, texture, NULL, &rect);
}
