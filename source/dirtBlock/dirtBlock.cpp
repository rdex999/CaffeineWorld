#include "dirtBlock.h"

dirtBlock::dirtBlock(base *baseObj, vector2d *location, SDL_Texture *textureDirt, SDL_Texture *textureDirtGrass,
    dirtBlock** dirtBlockArray, int dirtBlockIndex)
{
    this->baseObj = baseObj;
    this->location = *location;
    this->textures[0] = textureDirt;
    this->textures[1] = textureDirtGrass;
    this->dirtBlockArray = dirtBlockArray;
    this->dirtBlockIndex = dirtBlockIndex;

    dirtBlockSize = vector2d(184, 176)/3;

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

    }
}

void dirtBlock::render()
{
    SDL_Rect rect = {location.X, location.Y, dirtBlockSize.X, dirtBlockSize.Y};
    SDL_RenderCopy(baseObj->mainRenderer, textures[currentTextureIndex], NULL, &rect);
}