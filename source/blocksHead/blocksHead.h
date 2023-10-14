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

        // the area that the player can build in
        vector2d playerBuildZone;

        // time since the last build event.
        double timeBuild;

        // finds a location that a block can be spawned on
        // (relative to player->standingBlock)
        // @param {vector2d*} where to find the location
        // @returns {vector2d} a location that you can spawn a block in
        vector2d findBlockSpawn(vector2d* near);

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
        // @param {bool} horizontal
        // if false then the Row will be vertical
        // @return index of the first nullptr in blocksArray
        int spawnRow(vector2d* from, int blockCount, itemId blockType,
            int fromIndex, SDL_Texture* texture1, SDL_Texture* texture2 = nullptr, bool horizontal = true);

        // Spawns multible rows
        // @param {int} rowCount
        // number of rows to spawn
        // @param {int} blocksPerRow
        // number of blocks in each row
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
        // @param {bool} horizontal
        // if false then the Row will be vertical
        // @return index of the first nullptr in blocksArray
        int spawnRows(int rowCount, int blocksPerRow, vector2d* from, itemId blockType,
            int fromIndex, SDL_Texture* texture1, SDL_Texture* texture2 = nullptr, bool horizontal = true);

        // Spawns a crooked row of blocks from a given location.
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
        int spawnCrookedRow(vector2d* from, int blockCount, itemId blockType,
            int fromIndex, SDL_Texture* texture1, SDL_Texture* texture2 = nullptr);

        // an array of all dirt blocks in the world
        block* blockArray[1500] = {nullptr};

        // the textures of the dirt blcks.
        // index 0 is dirt texture, index 1 is dirtGrass texture
        SDL_Texture* texturesDirtBlock[2];

        // keep track of the next block index in the blocks array
        int blockIndexCounter;
};