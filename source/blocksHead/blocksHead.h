#pragma once
#include "../base/base.h"
#include "../player/player.h"
#include "../block/block.h"

class blocksHead
{
    public:
        blocksHead(base* baseObj, player* playerObj);
        ~blocksHead();

        // runs every frame
        void tick();

    private:

        // store baseObj and playerObj pointers
        base* baseObj;
        player* playerObj;

        // Spawns a row of block from a given location.
        // @param {vector2d} from
        // from where to start the row
        // @param {int} blockCount
        // how many blocks to spawn
        // @param {int} blockType
        // blockType = 1: dirt/grass
        // blockType = 2: stone
        // blockType = 3: wood
        // @param {int} fromIndex
        // from where to start spawning blocks in the blocks array
        // if not specified, the function will search for empty spaces in the blocks array and spawn the blocks in them.
        // @return index of the first nullptr in blocksArray
        int spawnRow(vector2d* from, int blockCount, int blockType,
            SDL_Texture* texture1, SDL_Texture* texture2, int fromIndex = -1);

        // an array of all dirt blocks in the world
        block* blockArray[60] = {nullptr};

        // the textures of the dirt blcks.
        // index 0 is dirt texture, index 1 is dirtGrass texture
        SDL_Texture* texturesDirtBlock[2];

        // keep track of the next block index in the blocks array
        int blockIndexCounter;
};