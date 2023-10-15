#include "attackHand.h"

attackHand::attackHand(base *baseObj, player* playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    // set the hand size
    handSize = vector2d(371, 168)/6;

    attack = false;

    attackOffset = 0.f;

    attackSlowDown = 3.f;

    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/attackHand/attackHand-v1.2.png");
    if(!texture){
        std::cout << "Error: could not create attackHand texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

}

attackHand::~attackHand()
{
    if(texture){SDL_DestroyTexture(texture);}
}

void attackHand::tick()
{
    render();

    if(baseObj->mouseState == 1 && !attack){
        attack = true;
        rotation = baseObj->rotationPlayerToMouse;
        direction = dVector2d(0, 0);
    }
    if(attack){
        attackSlowDown -= baseObj->deltaTime * 15;
        attackOffset += baseObj->deltaTime * 1510 * attackSlowDown;
        if(attackOffset <= 0){
            attack = false;
            attackOffset = 0.f;
            attackSlowDown = 3.f;
        }
        if(playerObj->flip){
            direction += dVector2d(std::cos(rotation*(M_PI/180)) * baseObj->deltaTime * attackOffset * attackSlowDown,
                std::sin(rotation*(M_PI/180)) * baseObj->deltaTime * attackOffset * attackSlowDown);
        }else{
            direction -= dVector2d(std::cos(rotation*(M_PI/180)) * baseObj->deltaTime * attackOffset * attackSlowDown,
                std::sin(rotation*(M_PI/180)) * baseObj->deltaTime * attackOffset * attackSlowDown);
        }
        screenLocation = playerObj->location + vector2d(direction.X, direction.Y + playerObj->location.H/2.7);
    }

}

void attackHand::render()
{
    if(attack){
        SDL_Rect rect = {screenLocation.X, screenLocation.Y, handSize.X, handSize.Y};
        SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &rect, rotation, NULL, SDL_RendererFlip(playerObj->flip));
    }
}
