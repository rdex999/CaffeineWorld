#include "attackHand.h"

attackHand::attackHand(base *baseObj, player* playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    // set the hand size
    handSize = vector2d(2274, 1034)/18;

    attack = false;


    attackOffset = 0.f;

    attackSlowDown = 3.f;

    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/attackHand/attackHand.png");
    if(!texture){
        std::cout << "Error: could not create attackHand texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    baseObj->boxes.insert(baseObj->boxes.end(), new box(std::bind(&attackHand::render, this),
        std::bind(&attackHand::tick, this, std::placeholders::_1)));
}

attackHand::~attackHand()
{
    if(texture){SDL_DestroyTexture(texture);}
}

void attackHand::tick(double deltaTime)
{
    if(playerObj->selectedItem == 1 && baseObj->mouseState == 1){
        attack = true;
    }
    if(attack){
        attackSlowDown -= deltaTime * 10;
        attackOffset += deltaTime * 230 * attackSlowDown;
        if(attackOffset <= 0){
            attack = false;
            attackOffset = 0.f;
            attackSlowDown = 3.f;
        }
        if(playerObj->flip){
            screenLocation = playerObj->screenLocation + vector2d(attackOffset, playerObj->playerSize.Y/2.7);
        }else{
            screenLocation = playerObj->screenLocation + vector2d(-1*attackOffset, playerObj->playerSize.Y/2.7);
        }
    }
}

void attackHand::render()
{
    if(attack){
        SDL_Rect rect = {screenLocation.X, screenLocation.Y, handSize.X, handSize.Y};
        SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &rect, 0, NULL, SDL_RendererFlip(playerObj->flip));
    }
}
