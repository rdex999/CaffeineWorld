#pragma once
#include "../base/base.h"

class dirtBlock
{
    public:
        dirtBlock(base* baseObj, vector2d *location, SDL_Texture* textureDirt, SDL_Texture* textureDirtGrass,
            dirtBlock** dirtBlockArray = nullptr, int dirtBlockIndex = 0);
        ~dirtBlock();

        // runs every frame
        void tick();

    private:

        // store base pointer
        base* baseObj;

        // renders the dirt block to the screen
        void render();

        // the location of the dirt block on the screen
        vector2d location;

        // the size of the dirt block
        vector2d dirtBlockSize;

        // there are two textures for the dirt block, one is dirt, and one is dirtGrass 
        SDL_Texture* textures[2];

        // if there is a dirtBlock array, then the dirt block can destroy itself and mark as nullptr in the array
        dirtBlock** dirtBlockArray;

        // the index of the dirt block in the dirtBlockArray (if there is one)
        int dirtBlockIndex;

        // the current texture that is being used in the textures array
        int currentTextureIndex;
};