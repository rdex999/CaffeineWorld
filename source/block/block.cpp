#include "block.h"

block::block(base *baseObj, player* playerObj, vector2d *location, int blockType, SDL_Texture *texture, SDL_Texture *texture2,
    block** blockArray, int blockIndex, int blockArraySize)
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

    this->location.W = 184/4;
    this->location.H = 176/4;
    
    timeGrassCheck = 0;

    blockAbove = false;

    isAbovePlayer = false;

    aboveCheck = false;

    currentTextureIndex = 0;

    switch (blockType)
    {
    case 1:
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
        for(int i=0; i<blockArraySize; i++){
            if(blockArray[i]){
                if(blockArray[i]->location == location - vector2d(0, location.H)){
                    blockAbove = true;
                    break;
                }else{
                    blockAbove = false;
                }
            }
        }
        if(blockType == 1){
            if(blockAbove){
                currentTextureIndex = 0;
            }else{
                currentTextureIndex = 1;
            }
        }
    }

    if(location.inBox(vector2d(0, 0), baseObj->screenSize) || 
        vector2d(location.X+location.W, location.Y+location.H).inBox(vector2d(0, 0), baseObj->screenSize))
    {
        render();

        if(blockType == 1){
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

            blockEvent = 0; 
            break;

        case 2:

            blockEvent = 0;
            break;

        case 3:

            blockEvent = 0;
            break;

        case 4:
            blockAbove = false;
            for(int i=0; i<blockArraySize; i++){
                if(blockArray[i]){
                    if(blockArray[i]->location+vector2d(0, location.H) == location){
                        blockAbove = true;
                        timeGrassCheck = 0;
                        break;
                    }
                }
            }

            blockEvent = 0;
            break;

        default:
            break;
        }

        timeLastHit = std::clamp(timeLastHit + baseObj->deltaTime, (double)0, (double)5);

        // if the players wants to destroy a block
        if(baseObj->mouseLocation.inBox(location, location+vector2d(location.W, location.H)) &&
            baseObj->mouseState == 1 && timeLastHit >= 0.39)
        {
            timeLastHit = 0;
            switch (playerObj->selectedItem)
            {
            case 1:
                blockLife -= 6;
                break;
            
            default:
                if(playerObj->selectedItem != 10){
                    blockLife -= 3;
                }
                break;
            }
            if(blockLife <= 0){
                for(int j=0; j<blockArraySize; j++){
                    if(blockArray[j]){
                        if(blockArray[j]->location+vector2d(location.W, 0) == location){
                            blockArray[j]->blockEvent = 1;
                        }else if(blockArray[j]->location == location+vector2d(location.W, 0)){
                            blockArray[j]->blockEvent = 2;
                        }else if(blockArray[j]->location+vector2d(0, location.H) == location){
                            blockArray[j]->blockEvent = 3;
                        }else if(blockArray[j]->location == location+vector2d(0, location.H)){
                            blockArray[j]->blockEvent = 4;
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
        //        
        //  COLLISION SECTION:
        //
        
        // if there is a block above the player then block the jump
        if(((location.X > playerObj->screenLocation.X &&
            location.X < playerObj->screenLocation.X+playerObj->screenLocation.W) ||
            (location.X+location.W > playerObj->screenLocation.X &&
            location.X+location.W < playerObj->screenLocation.X+playerObj->screenLocation.W)) &&
            location.Y + location.H >= playerObj->screenLocation.Y && 
            location.Y + location.H <= playerObj->screenLocation.Y + playerObj->screenLocation.H/5)
        {
            playerObj->screenLocation.Y += (location.Y+location.H)-playerObj->screenLocation.Y;
            playerObj->jump = false;
            playerObj->jumpIntensity = 10;
            isAbovePlayer = true; 
        }else{
            isAbovePlayer = false;
        }

        // if the player is blocked by a high wall (when the wall is on the right)
        if(playerObj->screenLocation.X+playerObj->screenLocation.W >= location.X &&
            playerObj->screenLocation.X+playerObj->screenLocation.W < location.X+location.W &&
            location.Y < playerObj->screenLocation.Y + playerObj->screenLocation.H/2 && 
            location.Y+location.H >= playerObj->screenLocation.Y &&
            !isAbovePlayer 
        )
        {
            playerObj->blockedRight = true;
            playerObj->screenLocation.X -= (playerObj->screenLocation.X+playerObj->screenLocation.W)-location.X;
        }

        // if the player is blocked by a high wall (when the wall is on the left)
        if(playerObj->screenLocation.X <= location.X+location.W &&
            playerObj->screenLocation.X > location.X && 
            location.Y < playerObj->screenLocation.Y + playerObj->screenLocation.H/2 && 
            location.Y+location.H >= playerObj->screenLocation.Y &&
            !isAbovePlayer 
        )
        {
            playerObj->blockedLeft = true;
            playerObj->screenLocation.X += (location.X+location.W)-playerObj->screenLocation.X;
        }

        // whether the player is standing on the block
        if(((location.X <= playerObj->screenLocation.X+playerObj->screenLocation.W &&
            location.X >= playerObj->screenLocation.X) || 
            (location.X+location.W <= playerObj->screenLocation.X+playerObj->screenLocation.W &&
            location.X+location.W >= playerObj->screenLocation.X))&&
            location.Y <= playerObj->screenLocation.Y+playerObj->screenLocation.H &&
            location.Y > playerObj->screenLocation.Y + playerObj->screenLocation.H/2 && 
            !blockAbove)
        {
            playerObj->inAir = false;
            playerObj->gravitySlowDown = 1.f; 
            playerObj->screenLocation.Y -= ((playerObj->screenLocation.Y+playerObj->screenLocation.H)-location.Y)*
                baseObj->deltaTime * 15; 
        }

    }
}

void block::render()
{
    SDL_Rect rect = {location.X, location.Y, location.W, location.H};
    SDL_RenderCopy(baseObj->mainRenderer, textures[currentTextureIndex], NULL, &rect);
}