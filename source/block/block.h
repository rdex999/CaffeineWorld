#pragma once
#include "../base/base.h"
#include "../player/player.h"

class block
{
    public:

        // block constructor.
        // @param {int} blockType
        // blockType = 1: dirt/grass
        // blockType = 2: stone
        // blockType = 3: wood
        // @param {SDL_Texture*} texture2
        // optional texture, used for dirt (as there is dirt and grass)
        // @param {int} blockArraySize
        // the size you gave the blocks array. (not the index of the last element)
        block(base* baseObj, player* playerObj, vector2d *location, int blockType, SDL_Texture* texture, SDL_Texture* texture2,
            block** blockArray, int blockIndex, int blockArraySize);
        ~block();

        // the type of the block
        // 1: dirt/grass
        // 2: stone
        // 3: wood
        int blockType;

        // runs every frame
        void tick();

        // the location of the dirt block on the screen
        vector2d location;

        // if there is a block above this one
        bool blockAbove;
    
    private:

        // store baseObj and playerObjpointers
        base* baseObj;
        player* playerObj;

        // renders the dirt block to the screen
        void render();

        // there are two textures for the dirt block, one is dirt, and one is dirtGrass 
        SDL_Texture* textures[2];

        // if there is a block array, then the dirt block can destroy itself and mark as nullptr in the array
        block** blockArray;

        // the index of the dirt block in the blockArray (if there is one)
        int blockIndex;

        double timeGrassCheck;

        // the current texture that is being used in the textures array
        int currentTextureIndex;

        // the length of the blocks array
        int blockArraySize;

        // if this block is above the players head
        bool isAbovePlayer;

        // if the block already checked if there is a block above this one
        bool aboveCheck;

};