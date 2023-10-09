#include "blocksHead.h"
#define BLOCKS_CAPASITY 1500
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

    // 
    // MAP CREATION SECTION
    //

    vector2d blockLocation(baseObj->screenSize.X*-5, baseObj->screenSize.Y/1.064);
    blockIndexCounter = 0;

    blockIndexCounter = spawnRows(2, 500, &blockLocation, 1, blockIndexCounter, texturesDirtBlock[0], texturesDirtBlock[1]);

    blockLocation += vector2d(B_W*30, -1*B_H);
    blockIndexCounter = spawnRow(&blockLocation, 7, 1, blockIndexCounter, texturesDirtBlock[0], texturesDirtBlock[1]);

    blockLocation.X += B_W*200;
    blockIndexCounter = spawnRow(&blockLocation, 30, 1, blockIndexCounter, texturesDirtBlock[0], texturesDirtBlock[1]);

}

blocksHead::~blocksHead()
{
    if(texturesDirtBlock[0]){SDL_DestroyTexture(texturesDirtBlock[0]);}
    if(texturesDirtBlock[1]){SDL_DestroyTexture(texturesDirtBlock[1]);}

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
    int fromIndex ,SDL_Texture* texture1, SDL_Texture* texture2, bool horizontal)
{
    vector2d location;
    int blocks = fromIndex; 
    for(int i=0; i<blockCount; i++){
        blocks++;
        if(horizontal){
            location = *from + vector2d(i*(B_W), 0);
        }else{
            location = *from - vector2d(0, i*(B_H));
        }
        
        blockArray[i + fromIndex] = new block(baseObj, playerObj, &location, blockType,
            texture1, texture2, blockArray, i+fromIndex, BLOCKS_CAPASITY);
    }
    return blocks;
}

int blocksHead::spawnRows(int rowCount, int blocksPerRow, vector2d *from, int blockType,
    int fromIndex ,SDL_Texture *texture1, SDL_Texture* texture2, bool horizontal)
{
    vector2d rowStart = *from; 
    int blocks = fromIndex;
    for(int i=0; i<rowCount; i++){
        if(horizontal){
            rowStart = *from + vector2d(0, B_H*i);
        }else{
            rowStart = *from + vector2d(B_W*i, 0);
        }
        
        blocks = spawnRow(&rowStart, blocksPerRow, blockType, blocks, texture1, texture2, horizontal);
    }
    return blocks;
}

int blocksHead::spawnCrookedRow(vector2d *from, int blockCount, int blockType, int fromIndex,
    SDL_Texture *texture1, SDL_Texture *texture2)
{
    vector2d location;
    for(int i=0; i<blockCount; i++){
        location = *from + vector2d(B_W*i, -1*B_H*i);
        blockArray[i + fromIndex] = new block(baseObj, playerObj, &location, blockType,
            texture1, texture2, blockArray, i+fromIndex, BLOCKS_CAPASITY);
    }
    return blockIndexCounter + blockCount;
}
