#pragma once
#include "../tree/tree.h"

class treesHead
{
    public:
        treesHead(base* baseObj, player* playerObj);
        ~treesHead();

        void tick();

        tree* trees[300] = {nullptr};

    private:

        base* baseObj;
        player* playerObj;

        SDL_Texture* textureTree;

};