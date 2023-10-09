#include "pickaxe.h"

pickaxe::pickaxe(base *baseObj, player *playerObj, int itemNum)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->itemNum = itemNum;

    rotation = 0;

    screenLocation = playerObj->screenLocation;

    mined = false;

    switch (itemNum)
    {
    case 1:
        texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/pickaxe/woodenPickaxe.png");
        pickaxeLife = 60;
        pickaxePower = 6;
        break;
    
    default:
        break;
    }

    if(!texture){
        std::cout << "Error: could not create wooden pickaxe texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
}

pickaxe::~pickaxe()
{
    if(texture){SDL_DestroyTexture(texture);}
}

void pickaxe::tick()
{
    if(playerObj->selectedItem == 1){
        render();

        if(baseObj->mouseState == 1 && !mined){
            mined = true;
            rotation = 0;
        }

        if(mined){
            rotation += baseObj->deltaTime*60;
            if(rotation >= 60){
                mined = false;
            }
        } 
    }
}

void pickaxe::render()
{
    if(playerObj->selectedItem == 1){
        SDL_Rect rect = {screenLocation.X, screenLocation.Y, screenLocation.W, screenLocation.H};
        SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &rect, rotation, NULL, SDL_RendererFlip(playerObj->flip));
    }
}
