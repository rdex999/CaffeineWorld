#include "worldUI.h"
#define HEART_W (int)(80/2.3)
#define HEART_H (int)(72/2.3)


worldUI::worldUI(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    textureHeartFull = IMG_LoadTexture(baseObj->mainRenderer, "./images/worldUI/hearts/hpHeartFull.png");
    if(!textureHeartFull){
        std::cout << "Error: could not create heart full texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    textureHeartEmpty = IMG_LoadTexture(baseObj->mainRenderer, "./images/worldUI/hearts/hpHeartEmpty.png");
    if(!textureHeartEmpty){
        std::cout << "Error: could not create heart empty texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    textureHeartFullHalf = IMG_LoadTexture(baseObj->mainRenderer, "./images/worldUI/hearts/hpHeartFullHalf.png");
    if(!textureHeartFullHalf){
        std::cout << "Error: could not create heart full half texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
}

worldUI::~worldUI()
{
    if(textureHeartFull){SDL_DestroyTexture(textureHeartFull);}
    if(textureHeartEmpty){SDL_DestroyTexture(textureHeartEmpty);}
}

void worldUI::tick()
{
    render();
}

void worldUI::render()
{
    SDL_Rect heartEmptyRect = {baseObj->screenSize.X/20, baseObj->screenSize.Y - baseObj->screenSize.Y/19, HEART_W, HEART_H};
    for(int i=0; i<10; i++){
        SDL_RenderCopy(baseObj->mainRenderer, textureHeartEmpty, NULL, &heartEmptyRect);
        heartEmptyRect.x += HEART_W + 10;

        if(playerObj->life - i > 0){
            SDL_RenderCopy(baseObj->mainRenderer, textureHeartFull, NULL, &heartEmptyRect);
        }
    }

    SDL_Rect heartFullRect = {baseObj->screenSize.X/20, baseObj->screenSize.Y - baseObj->screenSize.Y/19, HEART_W, HEART_H};
    for(int i=0; i<playerObj->life; i++){
        SDL_RenderCopy(baseObj->mainRenderer, textureHeartFull, NULL, &heartFullRect);
        heartFullRect.x += HEART_W + 10;

        if(playerObj->life - i == 0.5){
            heartFullRect.w /= 2; 
            SDL_RenderCopy(baseObj->mainRenderer, textureHeartFullHalf, NULL, &heartFullRect);

        }
    }

}