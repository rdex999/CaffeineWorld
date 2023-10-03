#include "blocksHead.h"

blocksHead::blocksHead(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;  
    
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
    for(int i=0; i<25; i++){
        if(i == 10){
            screenStart.Y -= 176/3;
        }
        if(i == 15){
            screenStart.Y -= 176/3;
        }
        dirtBlockArray[i] = new dirtBlock(baseObj, playerObj, &screenStart, texturesDirtBlock[0], texturesDirtBlock[1],
            dirtBlockArray, i);
        screenStart.X += 184/3.1;
        if(i == 15){
            screenStart.Y -= 176/3;
            screenStart.X -= 184/3.1;
        }
        if(i == 16){
            screenStart.Y -= 176/3;
            screenStart.X -= 184/3.1;
        }
        if(i == 17){
            screenStart.Y += 176/3*2;
        }
        if(i == 20){
            screenStart.Y += 176/3;
        }
    }
}

blocksHead::~blocksHead()
{
    for(int i=0;i <25; i++){
        if(dirtBlockArray[i]){
            delete dirtBlockArray[i];
        }
    }
}

void blocksHead::tick()
{
    playerObj->inAir = true;
    playerObj->blockedRight = false;
    playerObj->blockedLeft = false;
    for(int i=0; i<25; i++){
        if(dirtBlockArray[i]){
            dirtBlockArray[i]->tick();
        }
    }
}
