#include "pickaxe.h"

pickaxe::pickaxe(base *baseObj, player *playerObj, itemId itemNum)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->itemNum = itemNum;

    rotation = 70;

    screenLocation = vector2d(playerObj->screenLocation.X + playerObj->screenLocation.W/2,
        playerObj->screenLocation.Y+playerObj->screenLocation.H/2.7);

    screenLocation.W = 499/7.5;
    screenLocation.H = 633/7.5;

    mined = false;

    switch (itemNum)
    {
    case itemWoodenPickaxe:
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
    render();

    if(baseObj->mouseState == 1 && !mined){
        mined = true;
        rotation = 70;
    }

    screenLocation.Y = playerObj->screenLocation.Y+playerObj->screenLocation.H/2.7 - screenLocation.H/1.3;
    if(playerObj->flip){
        rotation = std::abs(rotation);
    
        screenLocation.X = playerObj->screenLocation.X + playerObj->screenLocation.W - screenLocation.W;
    }else{
        rotation = -std::abs(rotation);
        screenLocation.X = playerObj->screenLocation.X + playerObj->screenLocation.W - screenLocation.W/1.1;
    }

    if(mined){
        if(playerObj->flip){
            rotation += baseObj->deltaTime*210;
            if(rotation >= 70*2){
                mined = false;
                rotation = 70;
            }
        }else{
            rotation -= baseObj->deltaTime*210;
            if(rotation <= -70*2){
                mined = false;
                rotation = -70;
            }
        }
    } 
}

void pickaxe::render()
{
    SDL_Rect rect = {screenLocation.X, screenLocation.Y, screenLocation.W, screenLocation.H};
    SDL_Point rotationCenter = {screenLocation.W/2, screenLocation.H};
    SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &rect, rotation, &rotationCenter, SDL_RendererFlip(playerObj->flip));
}
