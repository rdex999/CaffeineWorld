#include "blocksHead.h"
#define BLOCKS_CAPASITY 43
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
    blockIndexCounter = 0;
    for(; blockIndexCounter<BLOCKS_CAPASITY; blockIndexCounter++){
        switch (blockIndexCounter)
        {
        case 7:
            blockLocation.Y -= 176/3; 
            break;

        case 13:
            blockLocation.Y -= 176/3;
            break;     

        case 14:
            blockLocation.Y -= 176/3;
            break;     

        case 15:
            blockLocation.Y -= 176/3;
            break;     

        case 16:
            blockLocation.Y -= 176/3;
            break;     

        case 17:
            blockLocation.X += 184/3;
            blockIndexCounter = spawnRow( &blockLocation, 5, 1, texturesDirtBlock[0], texturesDirtBlock[1], blockIndexCounter);
            blockLocation.Y += 176/3*4; 
            break;


        default:
            blockLocation.X += 184/3; 
        } 
        
        blockArray[blockIndexCounter] = new block(baseObj, playerObj, &blockLocation, 1,
            texturesDirtBlock[0], texturesDirtBlock[1], blockArray, blockIndexCounter, BLOCKS_CAPASITY);
    }
}

blocksHead::~blocksHead()
{
    for(int i=0;i <BLOCKS_CAPASITY; i++){
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
    for(int i=0; i<BLOCKS_CAPASITY; i++){
        if(blockArray[i]){
            blockArray[i]->tick();
        }
    }
}

int blocksHead::spawnRow(vector2d* from, int blockCount, int blockType,
    SDL_Texture* texture1, SDL_Texture* texture2, int fromIndex)
{
    vector2d location;
    for(int i=0; i<blockCount; i++){
        location = *from + vector2d(i*(184/3), 0);
        if(fromIndex != -1){
            blockArray[i + fromIndex] = new block(baseObj, playerObj, &location, blockType,
                texture1, texture2, blockArray, i+fromIndex, BLOCKS_CAPASITY);
        }
    }
    if(fromIndex != -1){
        return blockIndexCounter + blockCount;
    }else{
        return 0;
    }
}
