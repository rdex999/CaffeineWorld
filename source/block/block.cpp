#include "block.h"
#define B_W 184/4
#define B_H 176/4

block::block(base *baseObj, player* playerObj, vector2d *location, itemId blockType, SDL_Texture *texture, SDL_Texture *texture2,
    block** blockArray, int blockIndex, int blockArraySize, SDL_Texture** texturesBlockBreaking)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->location = *location;
    this->blockType = blockType;
    this->textures[0] = texture;
    this->textures[1] = texture2;
    this->blockArray = blockArray;
    this->blockIndex = blockIndex;
    this->blockArraySize = blockArraySize;
    this->texturesBlockBreaking = texturesBlockBreaking;
    this->location.W = B_W;
    this->location.H = B_H;
    
    timeGrassCheck = 0;

    blockAbove = false;

    isAbovePlayer = false;

    aboveCheck = false;

    currentTextureIndex = 0;

    blockBreakingIndex = -1;
    
    playerZone = playerObj->location - playerObj->location.W;
    playerZone.W = playerObj->location.W*3;
    playerZone.H = playerObj->location.W*2 + playerObj->location.H;

    switch (blockType)
    {
    case itemGrassBlock:
        blockLife = 15; 
        break;
    
    default:
        break;
    }
    maxBlockLife = blockLife;

}

block::~block()
{
    if(blockArray)
        blockArray[blockIndex] = nullptr;
}

void block::tick()
{
    location += baseObj->screenOffset;

    // everything in this if statement runs only once.
    // i did this because this code needs to run after all the blocks have been created.
    if(!aboveCheck){
        aboveCheck = true;
        bool leftCheck = false;
        bool belowCheck = false;
        for(int i=0; i<blockArraySize; i++){
            if(blockArray[i]){
                
                // if there is a block above this one
                if(blockArray[i]->location == location - vector2d(0, B_H)){
                    blockAbove = true;
                    if(leftCheck && belowCheck){
                        break;
                    }
                }

                // if this block is on the right of blockArray[i]
                if(location + vector2d(B_W, 0) == blockArray[i]->location){
                    leftCheck = true;
                    location.W *= 1.5;
                    if(blockAbove && belowCheck){
                        break;
                    }
                }
                
                // if this block is above a block
                if(location + vector2d(0, B_H) == blockArray[i]->location){
                    belowCheck = true;
                    location.H *= 1.5;
                    if(blockAbove && leftCheck){
                        break;
                    }
                }
            }
        }
        if(blockType == itemGrassBlock){
            if(blockAbove){
                currentTextureIndex = 0;
            }else{
                currentTextureIndex = 1;
            }
        }
    }

    if(location.inBox(vector2d(-baseObj->screenSize.W, -baseObj->screenSize.W),
        baseObj->screenSize + baseObj->screenSize.W) || 
        vector2d(location.X+location.W, location.Y+location.H).
        inBox(vector2d(-baseObj->screenSize.W, -baseObj->screenSize.W),
        baseObj->screenSize + baseObj->screenSize.W))
    {
        render();

        // update the playerZone
        playerZone = playerObj->location - playerObj->location.W;
        playerZone.W = playerObj->location.W*3;
        playerZone.H = playerObj->location.W*2 + playerObj->location.H;

        if(blockType == itemGrassBlock){
            timeGrassCheck = std::clamp(timeGrassCheck + baseObj->deltaTime, (double)0, (double)10);
            if(timeGrassCheck >= 10){
                timeGrassCheck = 0;
                if(blockAbove){
                    currentTextureIndex = 0;
                }else{
                    currentTextureIndex = 1;
                }
            }
        }

        switch (blockEvent)
        {
        case 1:
            location.W /= 1.5;
            blockEvent = 0;
            break;

        case 2:

            blockEvent = 0;
            break;

        case 3:
            location.H /= 1.5;
            blockEvent = 0;
            break;

        case 4:
            blockAbove = false;
            for(int i=0; i<blockArraySize; i++){
                if(blockArray[i]){
                    if(blockArray[i]->location+vector2d(0, B_H) == location){
                        blockAbove = true;
                        break;
                    }
                }
            }
            timeGrassCheck = 0;

            blockEvent = 0;
            break;

        case 5:
            location.W *= 1.5;

            blockEvent = 0;
            break;

        case 6:

            blockEvent = 0;
            break;

        case 7:
            location.H *= 1.5;

            blockEvent = 0;
            break;

        case 8:
            blockAbove = true;
            if(blockType == itemGrassBlock){
                currentTextureIndex = 0;
            }

            blockEvent = 0;
            break;

        default:
            break;
        }

        timeLastHit = std::clamp(timeLastHit + baseObj->deltaTime, (double)0, (double)5);

        // if the players wants to destroy a block
        if(baseObj->mouseLocation.inBox(location, location+vector2d(B_W, B_H)) &&
            baseObj->mouseState == 1 && timeLastHit >= 0.33 &&
            (location.inBox(playerZone, playerZone+vector2d(playerZone.W, playerZone.H)) ||
            (location+vector2d(B_W, B_H)).inBox(playerZone, playerZone+vector2d(playerZone.W, playerZone.H))))
        {

            // will change this in the future
            if(playerObj->selectedItemIndex != -1){
                timeLastHit = 0;
                switch (playerObj->items[playerObj->selectedItemIndex]->itemID)
                {
                case itemWoodenPickaxe:
                    blockLife -= 6;
                    break;

                default:
                    if(playerObj->items[playerObj->selectedItemIndex]->itemID != itemGun){
                        blockLife -= 3;
                    }
                    break;
                }
            }else{
                blockLife -= 3;
            }
            if(blockLife <= 0){
                for(int j=0; j<blockArraySize; j++){
                    if(blockArray[j]){
                        if(blockArray[j]->location+vector2d(B_W, 0) == location){
                            blockArray[j]->blockEvent = 1;
                        }else if(blockArray[j]->location == location+vector2d(B_W, 0)){
                            blockArray[j]->blockEvent = 2;
                        }else if(blockArray[j]->location+vector2d(0, B_H) == location){
                            blockArray[j]->blockEvent = 3;
                        }else if(blockArray[j]->location == location+vector2d(0, B_H)){
                            blockArray[j]->blockEvent = 4;
                        }
                    }
                }

                // if there is no item with the same blockType, then add it
                if(searchPlayerItem(blockType, true) == -1){
                    for(int i=0; i<INVENTORY_CAPACITY; i++){
                        if(!playerObj->items[i]){
                            playerObj->items[i] = new item(blockType, 1, true);
                            break;
                        }
                    }
                }

                delete this;
            }
        
        }

        // regenerate block health 
        if(timeLastHit >= 4.1){
            blockLife = std::clamp(blockLife+3, 0, maxBlockLife);
        }

        if((float)blockLife / (float)maxBlockLife <= 0.3){
            blockBreakingIndex = 2; 
       
        }else if((float)blockLife / (float)maxBlockLife <= 0.6){
            blockBreakingIndex = 1; 
        
        }else if((float)blockLife / (float)maxBlockLife <= 0.9){
            blockBreakingIndex = 0; 
        
        }else{
            blockBreakingIndex = -1;
        }

        //        
        //  COLLISION SECTION:
        //
        playerCollision();

        if(baseObj->entityArray){
            entityCollision();
        } 
    }
}

void block::render()
{
    SDL_Rect rect = {location.X, location.Y, location.W, location.H};
    SDL_RenderCopy(baseObj->mainRenderer, textures[currentTextureIndex], NULL, &rect);

    if(blockBreakingIndex != -1){
        SDL_RenderCopy(baseObj->mainRenderer, texturesBlockBreaking[blockBreakingIndex], NULL, &rect);
    }
}

int block::searchPlayerItem(itemId type, bool increase)
{
    for(int i=0; i<INVENTORY_CAPACITY; i++){
        if(playerObj->items[i] && playerObj->items[i]->itemID == type){
            if(increase){
                playerObj->items[i]->count += 1;
                playerObj->items[i]->countEvent = true;
            }
            return i;
        }
    }
    return -1;
}

void block::entityCollision()
{
    for(int i=0; i<baseObj->entityArrayLength; i++){
        if(baseObj->entityArray[i])
        {
            // if there is a block above the player then block the jump
            if(((location.X > baseObj->entityArray[i]->location.X &&
                location.X < baseObj->entityArray[i]->location.X+baseObj->entityArray[i]->location.W) ||
                (location.X+B_W > baseObj->entityArray[i]->location.X &&
                location.X+B_W < baseObj->entityArray[i]->location.X+baseObj->entityArray[i]->location.W)) &&
                location.Y + B_H >= baseObj->entityArray[i]->location.Y && 
                location.Y + B_H <= baseObj->entityArray[i]->location.Y + baseObj->entityArray[i]->location.H/5)
            {
                baseObj->entityArray[i]->location.Y += (location.Y+B_H)-baseObj->entityArray[i]->location.Y;
                baseObj->entityArray[i]->jump = false;
                baseObj->entityArray[i]->jumpIntensity = 10;
            }else{
            }

            // if the player is blocked by a high wall (when the wall is on the right)
            if(baseObj->entityArray[i]->location.X+baseObj->entityArray[i]->location.W >= location.X &&
                baseObj->entityArray[i]->location.X+baseObj->entityArray[i]->location.W < location.X+B_W &&
                location.Y < baseObj->entityArray[i]->location.Y + baseObj->entityArray[i]->location.H/2 && 
                location.Y+B_H >= baseObj->entityArray[i]->location.Y
            )
            {
                baseObj->entityArray[i]->blockedRight = true;
                baseObj->entityArray[i]->location.X -= (baseObj->entityArray[i]->location.X+
                    baseObj->entityArray[i]->location.W)-location.X;
            }

            // if the player is blocked by a high wall (when the wall is on the left)
            if(baseObj->entityArray[i]->location.X <= location.X+B_W &&
                baseObj->entityArray[i]->location.X > location.X && 
                location.Y < baseObj->entityArray[i]->location.Y + baseObj->entityArray[i]->location.H/2 && 
                location.Y+B_H >= baseObj->entityArray[i]->location.Y
            )
            {
                baseObj->entityArray[i]->blockedLeft = true;
                baseObj->entityArray[i]->location.X += (location.X+B_W)-baseObj->entityArray[i]->location.X;
            }

            // whether the player is standing on the block
            if(((location.X <= baseObj->entityArray[i]->location.X+baseObj->entityArray[i]->location.W &&
                location.X >= baseObj->entityArray[i]->location.X) || 
                (location.X+B_W <= baseObj->entityArray[i]->location.X+baseObj->entityArray[i]->location.W &&
                location.X+B_W >= baseObj->entityArray[i]->location.X))&&
                location.Y <= baseObj->entityArray[i]->location.Y+baseObj->entityArray[i]->location.H &&
                location.Y > baseObj->entityArray[i]->location.Y + baseObj->entityArray[i]->location.H/2 && 
                !blockAbove)
            {
                baseObj->entityArray[i]->inAir = false;
                baseObj->entityArray[i]->gravitySlowDown = 1.f; 
                baseObj->entityArray[i]->location.Y -= ((baseObj->entityArray[i]->location.Y+
                    baseObj->entityArray[i]->location.H)-location.Y)*
                    baseObj->deltaTime * 15; 
            }
        }
    }
}

void block::playerCollision()
{
    // if there is a block above the player then block the jump
    if(((location.X > playerObj->location.X &&
        location.X < playerObj->location.X+playerObj->location.W) ||
        (location.X+location.W > playerObj->location.X &&
        location.X+location.W < playerObj->location.X+playerObj->location.W)) &&
        location.Y + location.H >= playerObj->location.Y && 
        location.Y + location.H <= playerObj->location.Y + playerObj->location.H/5)
    {
        playerObj->location.Y += (location.Y+location.H)-playerObj->location.Y;
        playerObj->jump = false;
        playerObj->jumpIntensity = 10;
        isAbovePlayer = true; 
    }else{
        isAbovePlayer = false;
    }

    // if the player is blocked by a high wall (when the wall is on the right)
    if(playerObj->location.X+playerObj->location.W >= location.X &&
        playerObj->location.X+playerObj->location.W < location.X+location.W &&
        location.Y < playerObj->location.Y + playerObj->location.H/2 && 
        location.Y+location.H >= playerObj->location.Y &&
        !isAbovePlayer 
    )
    {
        playerObj->blockedRight = true;
        playerObj->location.X -= (playerObj->location.X+playerObj->location.W)-location.X;
    }

    // if the player is blocked by a high wall (when the wall is on the left)
    if(playerObj->location.X <= location.X+location.W &&
        playerObj->location.X > location.X && 
        location.Y < playerObj->location.Y + playerObj->location.H/2 && 
        location.Y+location.H >= playerObj->location.Y &&
        !isAbovePlayer 
    )
    {
        playerObj->blockedLeft = true;
        playerObj->location.X += (location.X+location.W)-playerObj->location.X;
    }

    // whether the player is standing on the block
    if(((location.X <= playerObj->location.X+playerObj->location.W &&
        location.X >= playerObj->location.X) || 
        (location.X+location.W <= playerObj->location.X+playerObj->location.W &&
        location.X+location.W >= playerObj->location.X))&&
        location.Y <= playerObj->location.Y+playerObj->location.H &&
        location.Y > playerObj->location.Y + playerObj->location.H/2 && 
        !blockAbove)
    {
        playerObj->inAir = false;
        playerObj->gravitySlowDown = 1.f; 
        playerObj->location.Y -= ((playerObj->location.Y+playerObj->location.H)-location.Y)*
            baseObj->deltaTime * 15; 
    }
}
