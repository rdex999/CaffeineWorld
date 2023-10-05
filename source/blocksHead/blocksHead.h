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

        // an array of all dirt blocks in the world
        block* blockArray[30] = {nullptr};

        // the textures of the dirt blcks.
        // index 0 is dirt texture, index 1 is dirtGrass texture
        SDL_Texture* texturesDirtBlock[2];
};