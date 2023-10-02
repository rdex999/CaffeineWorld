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

    texturesDirtBlock[0] = IMG_LoadTexture(baseObj->mainRenderer, "./images/dirtBlock/dirtBlock-v1.1.png");
    if(!texturesDirtBlock[0]){
        std::cout << "Error: could not create dirtBlock texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    texturesDirtBlock[1] = IMG_LoadTexture(baseObj->mainRenderer, "./images/dirtBlock/dirtGrassBlock-v1.1.png");
    if(!texturesDirtBlock[1]){
        std::cout << "Error: could not create dirtGrassBlock texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    // create all the dirt blocks
    vector2d screenStart(0, baseObj->screenSize.Y/1.064);
    for(int i=0; i<10; i++){
        dirtBlockArray[i] = new dirtBlock(baseObj, &screenStart, texturesDirtBlock[0], texturesDirtBlock[1],
            dirtBlockArray, i);

        screenStart.X += 184/3.1;
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
    for(int i=0; i<10; i++){
        if(dirtBlockArray[i]){
            delete dirtBlockArray[i];
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
    for(int i=0; i<10; i++){
        if(dirtBlockArray[i]){
            dirtBlockArray[i]->tick();
        } 
    }
}