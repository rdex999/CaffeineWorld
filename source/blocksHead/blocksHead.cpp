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
    // W: 184/3
    // H: 176/3
    vector2d blockLocation(0, baseObj->screenSize.Y/1.064);
    int blockCounter = 0;
    for(; blockCounter<30; blockCounter++){
        switch (blockCounter)
        {
        case 7:
            blockLocation.Y -= 176/3;
            break;

        case 16:
            blockLocation.Y -= 176/3;
            break;

        case 17:
            blockLocation.Y -= 176/3;
            break;

        case 18:
            blockLocation.Y -= 176/3;
            break;

        case 19:
            blockLocation.Y -= 176/3;
            break;

        case 25:
            blockLocation.Y += 176/3 * 4; 
            break;

        default:
            blockLocation.X += 184/3;
            break;
        }

        blockArray[blockCounter] = new block(baseObj, playerObj, &blockLocation, 1,
            texturesDirtBlock[0], texturesDirtBlock[1], blockArray, blockCounter, 30);
    }
}

blocksHead::~blocksHead()
{
    for(int i=0;i <30; i++){
        if(blockArray[i]){
            delete blockArray[i];
        }
    }
}

void blocksHead::tick()
{
    playerObj->inAir = true;
    playerObj->blockedRight = false;
    playerObj->blockedLeft = false;
    for(int i=0; i<30; i++){
        if(blockArray[i]){
            blockArray[i]->tick();
        }
    }
}
