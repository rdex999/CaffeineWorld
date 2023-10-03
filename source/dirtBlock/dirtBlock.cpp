#include "dirtBlock.h"

dirtBlock::dirtBlock(base *baseObj, player* playerObj, vector2d *location, SDL_Texture *textureDirt, SDL_Texture *textureDirtGrass,
    dirtBlock** dirtBlockArray, int dirtBlockIndex)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->location = *location;
    this->textures[0] = textureDirt;
    this->textures[1] = textureDirtGrass;
    this->dirtBlockArray = dirtBlockArray;
    this->dirtBlockIndex = dirtBlockIndex;

    this->location.W = 184/3;
    this->location.H = 176/3;
    
    currentTextureIndex = 1;
}

dirtBlock::~dirtBlock()
{
    if(textures[0]){SDL_DestroyTexture(textures[0]);}
    if(textures[1]){SDL_DestroyTexture(textures[1]);}

    if(dirtBlockArray)
        dirtBlockArray[dirtBlockIndex] = nullptr;
}

void dirtBlock::tick()
{
    if(location.inBox(vector2d(0, 0), baseObj->screenSize)){
        render();

        // if the player is blocked by a high wall (when the wall is on the right)
        if(playerObj->screenLocation.X+playerObj->screenLocation.W >= location.X &&
            playerObj->screenLocation.X+playerObj->screenLocation.W < location.X+location.W &&
            location.Y < playerObj->screenLocation.Y + playerObj->screenLocation.H/2 
        )
        {
            playerObj->blockedRight = true;
            playerObj->screenLocation.X -= ((playerObj->screenLocation.X+playerObj->screenLocation.W)-location.X);
        }

        // if the player is blocked by a high wall (when the wall is on the left)
        if(playerObj->screenLocation.X <= location.X+location.W &&
            playerObj->screenLocation.X > location.X && 
            location.Y < playerObj->screenLocation.Y + playerObj->screenLocation.H/2
        )
        {
            playerObj->blockedLeft = true;
            playerObj->screenLocation.X += (location.X+location.W)-playerObj->screenLocation.X;
        }

        // whether the player is standing on the dirtBlock
        if(((location.X <= playerObj->screenLocation.X+playerObj->screenLocation.W &&
            location.X >= playerObj->screenLocation.X) || 
            (location.X+location.W <= playerObj->screenLocation.X+playerObj->screenLocation.W &&
            location.X+location.W >= playerObj->screenLocation.X))&&
            location.Y <= playerObj->screenLocation.Y+playerObj->screenLocation.H &&
            location.Y > playerObj->screenLocation.Y + playerObj->screenLocation.H/1.67)
        {
            playerObj->inAir = false;
            playerObj->gravitySlowDown = 1.f; 
            playerObj->screenLocation.Y -= ((playerObj->screenLocation.Y+playerObj->screenLocation.H)-location.Y)*
                baseObj->deltaTime * 15;
        }
    }
}

void dirtBlock::render()
{
    SDL_Rect rect = {location.X, location.Y, location.W, location.H};
    SDL_RenderCopy(baseObj->mainRenderer, textures[currentTextureIndex], NULL, &rect);
}