#pragma once
#include "../player/player.h"

class worldUI
{
    public:
        worldUI(base* baseObj, player* playerObj);
        ~worldUI();

        void tick();

    private:

        base* baseObj;
        player* playerObj;

        void render();

        SDL_Texture* textureHeartFull;
        SDL_Texture* textureHeartEmpty;
        SDL_Texture* textureHeartFullHalf;

};