#include "blocksHead.h"
#define BLOCKS_CAPASITY 1500
#define B_W 184/4
#define B_H 176/4

blocksHead::blocksHead(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;  

    timeBuild = 0;

    texturesDirtBlock[0] = IMG_LoadTexture(baseObj->mainRenderer, "./images/dirtBlock/dirtBlock-v1.2.png");
    if(!texturesDirtBlock[0]){
        std::cout << "Error: could not create dirtBlock texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    texturesDirtBlock[1] = IMG_LoadTexture(baseObj->mainRenderer, "./images/dirtBlock/dirtGrassBlock-v1.3.png");
    if(!texturesDirtBlock[1]){
        std::cout << "Error: could not create dirtGrassBlock texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    // 
    // MAP CREATION SECTION
    //

    vector2d blockLocation(baseObj->screenSize.X*-5, baseObj->screenSize.Y/1.064);
    blockIndexCounter = 0;

    blockIndexCounter = spawnRows(2, 500, &blockLocation, itemGrassBlock, blockIndexCounter, texturesDirtBlock[0], texturesDirtBlock[1]);

    blockLocation += vector2d(B_W*30, -1*B_H);
    blockIndexCounter = spawnRow(&blockLocation, 7, itemGrassBlock, blockIndexCounter, texturesDirtBlock[0], texturesDirtBlock[1]);

    blockLocation.X += B_W*200;
    blockIndexCounter = spawnRow(&blockLocation, 30, itemGrassBlock, blockIndexCounter, texturesDirtBlock[0], texturesDirtBlock[1]);

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
    playerBuildZone = playerObj->screenLocation - playerObj->screenLocation.W*5;
    playerBuildZone.W = playerObj->screenLocation.W*11;
    playerBuildZone.H = playerObj->screenLocation.W*11;

    timeBuild = std::clamp(timeBuild+baseObj->deltaTime, (double)0, (double)10);
    
    if(baseObj->mouseLocation.inBox(playerBuildZone, playerBuildZone+vector2d(playerBuildZone.W, playerBuildZone.W)) &&
        baseObj->mouseState == 4 && timeBuild >= 0.3 &&
        /* there will be more blocks in the future, this just checks if the selected item is a block */ 
        playerObj->selectedItem >= itemGrassBlock && playerObj->selectedItem <= itemGrassBlock)
                  
    {

        // the location of the block to spawn
        vector2d blockLoc = findBlockSpawn(&baseObj->mouseLocation);
    
        // the index of a block that is nullptr.
        // if still -1 after the loop then there is already a block
        // as blockLoc and cannot spawn a new one here. 
        int nullIdx = -1;

        for(int i=0; i<BLOCKS_CAPASITY; i++){
            if(blockArray[i] == nullptr && nullIdx == -1){
                nullIdx = i;
            }
            if(blockArray[i] && blockArray[i]->location == blockLoc){
                nullIdx = -1;
                break;
            }
        }

        if(nullIdx != -1 && playerObj->items[playerObj->selectedItemIndex].count >= 1){
            timeBuild = 0;
            if(blockArray[nullIdx] == nullptr){
            
                // switch on the block type. 
                switch (playerObj->selectedItem)
                {
                case itemGrassBlock:
                    blockArray[nullIdx] = new block(baseObj, playerObj, &blockLoc, itemGrassBlock,
                        texturesDirtBlock[0], texturesDirtBlock[1], blockArray, nullIdx, BLOCKS_CAPASITY);
                    
                    break;

                default:
                    break;
                }

                playerObj->items[playerObj->selectedItemIndex].count -= 1;
                if(playerObj->items[playerObj->selectedItemIndex].count <= 0){
                    playerObj->items[playerObj->selectedItemIndex].itemID = 0;
                }
                playerObj->items[playerObj->selectedItemIndex].countEvent = true;
            }
        }
    }

    playerObj->inAir = true;
    playerObj->blockedRight = false;
    playerObj->blockedLeft = false;
    for(int i=0; i<BLOCKS_CAPASITY; i++){
        if(blockArray[i]){
            blockArray[i]->tick();
        }
    }
}

vector2d blocksHead::findBlockSpawn(vector2d* near)
{
    vector2d closest = playerObj->standingBlock;

    if(closest.X < near->X){
        while(closest.X + B_W < near->X){
            closest.X += B_W;
        }
    }else{
        while(closest.X > near->X){
            closest.X -= B_W;
        }
 
    }

    if(closest.Y > near->Y){
        while (closest.Y > near->Y){
            closest.Y -= B_H;
        }
    }else{
        while (closest.Y + B_H < near->Y){
            closest.Y += B_H;
        }
        
    }

    return closest;
}

int blocksHead::spawnRow(vector2d *from, int blockCount, itemId blockType,
    int fromIndex, SDL_Texture *texture1, SDL_Texture *texture2, bool horizontal)
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

int blocksHead::spawnRows(int rowCount, int blocksPerRow, vector2d *from, itemId blockType,
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

int blocksHead::spawnCrookedRow(vector2d *from, int blockCount, itemId blockType, int fromIndex,
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
