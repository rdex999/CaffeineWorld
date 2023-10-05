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

    this->location.W = 184/3;
    this->location.H = 176/3;
    
    timeGrassCheck = 0;

    blockAbove = false;

    currentTextureIndex = 0;
}

block::~block()
{
    if(textures[0]){SDL_DestroyTexture(textures[0]);}
    if(textures[1]){SDL_DestroyTexture(textures[1]);}

    if(blockArray)
        blockArray[blockIndex] = nullptr;
}

void block::tick()
{
    if(location.inBox(vector2d(0, 0), baseObj->screenSize)){
        render();

        for(int i=0; i<blockArraySize; i++){
            if(blockArray[i]->location == location - vector2d(0, location.H)){
                blockAbove = true;
                break;
            }else{
                blockAbove = false;
            }
        }

        if(timeGrassCheck >= 3 && !blockAbove && blockType == 1){
            currentTextureIndex = 1;
        }
        timeGrassCheck = std::clamp(timeGrassCheck + baseObj->deltaTime, (double)0, (double)10);

        //        
        //  COLLISION SECTION:
        //

        // if the player is blocked by a high wall (when the wall is on the right)
        if(playerObj->screenLocation.X+playerObj->screenLocation.W >= location.X &&
            playerObj->screenLocation.X+playerObj->screenLocation.W < location.X+location.W &&
            location.Y < playerObj->screenLocation.Y + playerObj->screenLocation.H/2 && 
            location.Y+location.H >= playerObj->screenLocation.Y
        )
        {
            playerObj->blockedRight = true;
            playerObj->screenLocation.X -= ((playerObj->screenLocation.X+playerObj->screenLocation.W)-location.X);
        }

        // if the player is blocked by a high wall (when the wall is on the left)
        if(playerObj->screenLocation.X <= location.X+location.W &&
            playerObj->screenLocation.X > location.X && 
            location.Y < playerObj->screenLocation.Y + playerObj->screenLocation.H/2 && 
            location.Y+location.H >= playerObj->screenLocation.Y
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