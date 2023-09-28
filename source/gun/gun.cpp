#include "gun.h"

gun::gun(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/gun/gun.png");
    if(!texture){
        std::cout << "Error: could not load gun texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    gunSize = vector2d(251, 130)/1.7;

    baseObj->boxes.insert(baseObj->boxes.end(), new box(std::bind(&gun::tick, this, std::placeholders::_1)));
}

gun::~gun()
{
    if(texture){SDL_DestroyTexture(texture);}
}

void gun::tick(double deltaTime)
{
    render();

    if(playerObj->flip){
        baseObj->rotationPlayerToMouse = atan2(baseObj->mouseLocation.Y - (int)(playerObj->screenLocation.Y+playerObj->playerSize.Y/2.7),
            baseObj->mouseLocation.X - playerObj->screenLocation.X)*180/M_PI;
    }else{
        baseObj->rotationPlayerToMouse = atan2(baseObj->mouseLocation.Y*-1 - (int)(playerObj->screenLocation.Y+playerObj->playerSize.Y/2.7)*-1,
            baseObj->mouseLocation.X*-1 - playerObj->screenLocation.X*-1)*180/M_PI;
    }
}

void gun::render()
{
    if(playerObj->selectedItem == 2){
        SDL_Rect rect = {(int)playerObj->screenLocation.X,
            (int)(playerObj->screenLocation.Y+playerObj->playerSize.Y/2.7), (int)gunSize.X, (int)gunSize.Y};

        SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &rect,
            baseObj->rotationPlayerToMouse, NULL, SDL_RendererFlip(playerObj->flip));
    }
}