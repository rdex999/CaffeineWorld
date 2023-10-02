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

    textureCoffeeCup = IMG_LoadTexture(baseObj->mainRenderer, "./images/coffeeCup/coffeeCup.png");
    if(!textureCoffeeCup){
        std::cout << "Error: could not create coffee cup texture.\n" << SDL_GetError() << std::endl;
        exit(1); 
    }
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

void background::tick()
{
    render();

    timeCoffeeCupSpawn += baseObj->deltaTime;
    if(currentCoffeeCupIndex < 10 && timeCoffeeCupSpawn >= 3){
        if(!coffeeCupArray[currentCoffeeCupIndex]){
            coffeeCupArray[currentCoffeeCupIndex] = new coffeeCup(baseObj, baseObj->randomRange(0, 2),
                textureCoffeeCup, coffeeCupArray, currentCoffeeCupIndex);
        }
        currentCoffeeCupIndex++;
        timeCoffeeCupSpawn = 0;
        if(currentCoffeeCupIndex >= 10){currentCoffeeCupIndex = 0;}
    }
}

void background::render()
{
    SDL_Rect rect = {0, 0, (int)baseObj->screenSize.X, (int)baseObj->screenSize.Y};
    SDL_RenderCopy(baseObj->mainRenderer, texture, NULL, &rect);

    for(int i=0; i<10; i++){
        if(coffeeCupArray[i]){
            coffeeCupArray[i]->tick();
        }
    }
}