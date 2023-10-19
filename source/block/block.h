#pragma once
#include "../base/base.h"
#include "../player/player.h"
#include "../inventory/items/items.h"

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
        // @param {SDL_Texture**} texturesBlockBreaking
        // a texture array of the block cracks (size is allways 3)
        // @param {entity**} entityArray
        // an array of entity pointers to handle collision on. (dont include the playerObj in it)
        // @param {int} entityArrayLength
        // the length of the entity array
        // the size you gave the blocks array. (not the index of the last element)
        block(base* baseObj, player* playerObj, vector2d *location, itemId blockType,
            SDL_Texture* texture, SDL_Texture* texture2,
            block** blockArray, int blockIndex, int blockArraySize, SDL_Texture** texturesBlockBreaking);

        ~block();

        // the type of the block
        itemId blockType;

        // runs every frame
        void tick();

        // the location of the dirt block on the screen
        vector2d location;

        // if there is a block above this one
        bool blockAbove;

        // if there was a block event.
        // 0 = no block event.
        // 1 = this block is on the left of a block that was destroyed
        // 2 = this block is on the right of a block that was destroyed
        // 3 = this block is above a block that was destroyed
        // 4 = this block is below a block that was destroyed
        // 5 = this block is on the left of a new block
        // 6 = this block is on the right of a new block
        // 7 = this block is above a new block
        // 8 = this block is below a new block
        int blockEvent;

    
    private:

        // store baseObj and playerObjpointers
        base* baseObj;
        player* playerObj;

        // renders the dirt block to the screen
        void render();

        // there are two textures for the dirt block, one is dirt, and one is dirtGrass 
        SDL_Texture* textures[2];

        // the textures of the block breaking
        SDL_Texture** texturesBlockBreaking;

        // if there is a block array, then the dirt block can destroy itself and mark as nullptr in the array
        block** blockArray;

        // the index of the dirt block in the blockArray (if there is one)
        int blockIndex;

        // index of the currect texture to render in the texturesBlockBreaking array
        int blockBreakingIndex;

        double timeGrassCheck;

        // the current texture that is being used in the textures array
        int currentTextureIndex;

        // the length of the blocks array
        int blockArraySize;

        // if this block is above the players head
        bool isAbovePlayer;

        // if the block already checked if there is a block above this one
        bool aboveCheck;

        double timeLastHit;

        // basicly the blocks HP
        // when the player hits the block the blocks hp goes down
        int blockLife;

        // the max block life. the normal block life can change, this is kind of a constant
        int maxBlockLife;

        vector2d playerZone;

        // searchs the player items array for an item that is a
        // block with the same block type as the argument
        // @param {int} the block type to find
        // @param {bool} if the block is found, increase the count by 1
        // @returns {int} the index, or -1 if not found
        int searchPlayerItem(itemId type, bool increase);

        // handles collision for all entitys in the entitys array
        void entityCollision();

        // specific collision for the player
        void playerCollision();
};