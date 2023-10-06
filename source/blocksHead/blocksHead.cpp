#include "blocksHead.h"
#define BLOCKS_CAPASITY 400
#define B_W 184/4
#define B_H 176/4

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

    // create all the blocks
    // W: 184/4
    // H: 176/4
    vector2d blockLocation(baseObj->screenSize.X*-2, baseObj->screenSize.Y/1.064);
    blockIndexCounter = 0;

    blockIndexCounter = spawnRows(3, 100, &blockLocation, 1, texturesDirtBlock[0], texturesDirtBlock[1], true, blockIndexCounter);
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
    SDL_Texture* texture1, SDL_Texture* texture2, bool horizontal, int fromIndex)
{
    vector2d location;
    for(int i=0; i<blockCount; i++){
        if(horizontal){
            location = *from + vector2d(i*(B_W), 0);
        }else{
            location = *from - vector2d(0, i*(B_H));
        }
        
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

int blocksHead::spawnRows(int rowCount, int blocksPerRow, vector2d *from, int blockType,
    SDL_Texture *texture1, SDL_Texture *texture2, bool horizontal, int fromIndex)
{
    vector2d rowStart = *from; 
    int blocks = fromIndex;
    for(int i=0; i<rowCount; i++){
        if(horizontal){
            rowStart = *from + vector2d(0, B_H*i);
        }else{
            rowStart = *from + vector2d(B_W*i, 0);
        }
        
        blocks += spawnRow(&rowStart, blocksPerRow, blockType, texture1, texture2, horizontal, blocks);
    }
    return blocks;
}
