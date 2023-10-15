#pragma once
#include "../zombie/zombie.h"

class entitysHead
{
    public:
        entitysHead(base* baseObj, player* playerObj);
        ~entitysHead();

        // runs every frame
        void tick();

    private:

        base* baseObj;
        player* playerObj;

        // the zombies array
        zombie* zombiesArray[10] = {nullptr};

        // an array of texture pointers for the zombies
        SDL_Texture* texturesZombie[3];

};