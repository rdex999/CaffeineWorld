#include "coffeeCup.h"

coffeeCup::coffeeCup(base *baseObj, bool direction, std::vector<box*>::iterator boxIterator,
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

    boxPtr = new box(std::bind(&coffeeCup::tick, this, std::placeholders::_1));
    baseObj->boxes.insert(boxIterator, boxPtr);
}

coffeeCup::~coffeeCup()
{
    if(texture){SDL_DestroyTexture(texture);}
    baseObj->boxes.erase(std::find(baseObj->boxes.begin(), baseObj->boxes.end(), boxPtr));
    if(coffeeCupArray){
        coffeeCupArray[coffeeCupArrayIndex] = nullptr;
    }
    if(boxPtr){delete boxPtr;}
}

void coffeeCup::tick(double deltaTime)
{
    render();

    if(!screenLocation.inBox(dVector2d(0, 0), dVector2d(baseObj->screenSize.X, baseObj->screenSize.Y))){
        delete this;
    }

    screenLocation += (direction - screenLocation).norm() * deltaTime * speed;
}

void coffeeCup::render()
{
    SDL_Rect rect = {(int)screenLocation.X, (int)screenLocation.Y, coffeeCupSize.X, coffeeCupSize.Y};
    SDL_RenderCopy(baseObj->mainRenderer, texture, NULL, &rect);
}
