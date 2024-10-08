#include "blocksHead.h"
#define BLOCKS_CAPASITY 1500
#define B_W 184/4
#define B_H 176/4
#define MAX_ENTITYS 10

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
    texturesDirtBlock[1] = IMG_LoadTexture(baseObj->mainRenderer, "./images/dirtBlock/dirtGrassBlock-v1.4.png");
    if(!texturesDirtBlock[1]){
        std::cout << "Error: could not create dirtGrassBlock texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    texturesBlockBreaking[0] = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/blockBreaking/blockBreaking1-v1.0.png");
    if(!texturesBlockBreaking[0]){
        std::cout << "Error: could not create block breaking 1 texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    texturesBlockBreaking[1] = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/blockBreaking/blockBreaking2-v1.0.png");
    if(!texturesBlockBreaking[1]){
        std::cout << "Error: could not create block breaking 2 texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    texturesBlockBreaking[2] = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/blockBreaking/blockBreaking3-v1.0.png");
    if(!texturesBlockBreaking[2]){
        std::cout << "Error: could not create block breaking 3 texture.\n" << SDL_GetError() << std::endl;
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
    
    if(texturesBlockBreaking[0]){SDL_DestroyTexture(texturesBlockBreaking[0]);}
    if(texturesBlockBreaking[1]){SDL_DestroyTexture(texturesBlockBreaking[1]);}
    if(texturesBlockBreaking[2]){SDL_DestroyTexture(texturesBlockBreaking[2]);}

    for(int i=0;i <BLOCKS_CAPASITY; i++){
        if(blockArray[i]){
            delete blockArray[i];
        }
    }
}

void blocksHead::tick()
{
    playerBuildZone = playerObj->location - playerObj->location.W*5;
    playerBuildZone.W = playerObj->location.W*11;
    playerBuildZone.H = playerObj->location.W*11;

    timeBuild = std::clamp(timeBuild+baseObj->deltaTime, (double)0, (double)10);
    
    if(baseObj->mouseLocation.inBox(playerBuildZone, playerBuildZone+vector2d(playerBuildZone.W, playerBuildZone.W)) &&
        baseObj->mouseState == 4 && timeBuild >= 0.3 && playerObj->selectedItemIndex != -1 &&
        playerObj->items[playerObj->selectedItemIndex] &&
        /* there will be more blocks in the future, this just checks if the selected item is a block */ 
        playerObj->items[playerObj->selectedItemIndex]->itemID >= itemGrassBlock &&
        playerObj->items[playerObj->selectedItemIndex]->itemID <= itemGrassBlock)
                  
    {

        // the location of the block to spawn
        vector2d blockLoc = findBlockSpawn(&baseObj->mouseLocation);
        if(blockLoc != vector2d(-1, -1)){

            // the index of a block that is nullptr.
            // if still -1 after the loop then there is already a block
            // at blockLoc and cannot spawn a new one here. 
            int nullIdx = -1;

            // the index of the block that is on the left of the new one
            // -1 if none
            int leftIndex = -1;

            // the index of the block that is below the new one
            // -1 if none
            int belowIndex = -1;

            // the index of the block that is above the new one
            // -1 if none
            int aboveIndex = -1;

            for(int i=0; i<BLOCKS_CAPASITY; i++){
                if(blockArray[i] == nullptr && nullIdx == -1){
                    nullIdx = i;
                }

                if(blockArray[i] && blockArray[i]->location == blockLoc){
                    nullIdx = -1;
                    break;
                }

                if(blockArray[i] && blockArray[i]->location + vector2d(B_W, 0) == blockLoc){
                    leftIndex = i;
                }

                if(blockArray[i] && blockArray[i]->location == blockLoc + vector2d(0, B_H)){
                    belowIndex = i;
                }

                if(blockArray[i] && blockArray[i]->location + vector2d(0, B_H) == blockLoc){
                    aboveIndex = i;
                }
            }

            for(int i=0; i<baseObj->treeArrayLength; i++){
                if(baseObj->trees[i]){
                    if(blockLoc.inBox(baseObj->trees[i]->location + baseObj->trees[i]->location.W/4.8,
                        baseObj->trees[i]->location.getWH() - vector2d(baseObj->trees[i]->location.W/2.5, 0)))
                    {
                        nullIdx = -1;
                        break;
                    }
                }
            }

            if(nullIdx != -1 && playerObj->items[playerObj->selectedItemIndex]->count >= 1){
                timeBuild = 0;
                if(blockArray[nullIdx] == nullptr){
                
                    blockArray[nullIdx] = new block(baseObj, playerObj, &blockLoc,
                        (itemId)playerObj->items[playerObj->selectedItemIndex]->itemID,
                        texturesDirtBlock[0], texturesDirtBlock[1], blockArray, nullIdx,
                        BLOCKS_CAPASITY, texturesBlockBreaking);

                    playerObj->items[playerObj->selectedItemIndex]->count -= 1;
                    playerObj->items[playerObj->selectedItemIndex]->countEvent = true;
                    if(playerObj->items[playerObj->selectedItemIndex]->count <= 0){
                        delete playerObj->items[playerObj->selectedItemIndex];
                        playerObj->items[playerObj->selectedItemIndex] = nullptr;
                    }

                    if(leftIndex != -1){
                        blockArray[leftIndex]->blockEvent = 5;
                    }

                    if(belowIndex != -1){
                        blockArray[belowIndex]->blockEvent = 8;
                    }

                    if(aboveIndex != -1){
                        blockArray[aboveIndex]->blockEvent = 7;
                    }
                }
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
    for(int i=0; i<BLOCKS_CAPASITY; i++){
        if(blockArray[i])
        {
            // if near is above blockArray[i] 
            if(near->inBoxRel(blockArray[i]->location - vector2d(0, B_H), vector2d(B_W, B_H))){
                return blockArray[i]->location - vector2d(0, B_H) + baseObj->screenOffset;
            }

            // if near on the top right of blockArray[i]
            if(near->inBoxRel(blockArray[i]->location + vector2d(B_W, -B_H), vector2d(B_W, B_H))){
                return blockArray[i]->location + vector2d(B_W, -B_H);
            }
        
            // if near is on the right of blockArray[i]
            if(near->inBoxRel(blockArray[i]->location + vector2d(B_W, 0), vector2d(B_W, B_H))){
                return blockArray[i]->location + vector2d(B_W, 0);
            }

            // if near is on the bottom right of blockArray[i]
            if(near->inBoxRel(blockArray[i]->location + vector2d(B_W, B_H), vector2d(B_W, B_H))){
                return blockArray[i]->location + vector2d(B_W, B_H);
            }

            // if near is below blockArray[i]
            if(near->inBoxRel(blockArray[i]->location + vector2d(0, B_H), vector2d(B_W, B_H))){
                return blockArray[i]->location + vector2d(0, B_H);
            }

            // if near is on the bottom left of blockArray[i]
            if(near->inBoxRel(blockArray[i]->location + vector2d(-B_W, B_H), vector2d(B_W, B_H))){
                return blockArray[i]->location + vector2d(-B_W, B_H);
            }

            // if near is on the left of blockArra[i]
            if(near->inBoxRel(blockArray[i]->location - vector2d(B_W, 0), vector2d(B_W, B_H))){
                return blockArray[i]->location - vector2d(B_W, 0);
            }

            // if near is on the top left of blockArray[i]
            if(near->inBoxRel(blockArray[i]->location - vector2d(B_W, B_H), vector2d(B_W,   B_H))){
                return blockArray[i]->location - vector2d(B_W, B_H);
            }
        }
    }

    return vector2d(-1, -1);

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
            texture1, texture2, blockArray, i+fromIndex, BLOCKS_CAPASITY, texturesBlockBreaking);
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
            texture1, texture2, blockArray, i+fromIndex, BLOCKS_CAPASITY, texturesBlockBreaking);
    }
    return blockIndexCounter + blockCount;
}
