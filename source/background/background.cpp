#include "background.h"

background::background(base* baseObj)
{
    //store the baseObj pointer
    this->baseObj = baseObj;

    currentCoffeeCupIndex = 0;

    // load the image and create a surface
    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/background/backgroundMain.png");
    if(!texture){
        std::cout << "Error: could not create background texture.\n" << SDL_GetError() << std::endl;
        exit(1); 
    }

    boxPtr = new box(std::bind(&background::tick, this, std::placeholders::_1));

    baseObj->boxes.insert(baseObj->boxes.end(), boxPtr);

}

background::~background()
{
    if(texture){
        SDL_DestroyTexture(texture);
    }
    for(int i=0; i<10; i++){
        if(coffeeCupArray[i]){
            delete coffeeCupArray[i];
        }
    }
}

void background::tick(double deltaTime)
{
    render();

    timeCoffeeCupSpawn += deltaTime;
    if(currentCoffeeCupIndex < 10 && timeCoffeeCupSpawn >= 3){
        if(!coffeeCupArray[currentCoffeeCupIndex]){
            coffeeCupArray[currentCoffeeCupIndex] = new coffeeCup(baseObj, baseObj->randomRange(0, 2),
                std::find(baseObj->boxes.begin(), baseObj->boxes.end(), boxPtr) + 1, 
                coffeeCupArray, currentCoffeeCupIndex); // + 1 so the coffee box will be after the background
        }
        currentCoffeeCupIndex++;
        timeCoffeeCupSpawn = 0;
    }
}

void background::render()
{
    SDL_Rect rect = {0, 0, (int)baseObj->screenSize.X, (int)baseObj->screenSize.Y};
    SDL_RenderCopy(baseObj->mainRenderer, texture, NULL, &rect);
}