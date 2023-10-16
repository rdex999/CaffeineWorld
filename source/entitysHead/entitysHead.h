#pragma once
#include "../zombie/zombie.h"

class entitysHead
{
    public:
        entitysHead(base* baseObj, player* playerObj);
        ~entitysHead();

        // runs every frame
        void tick();

        // an array of entity pointers 
        entity* entityArray[10] = {nullptr};
    
    private:

        base* baseObj;
        player* playerObj;


        // an array of texture pointers for the zombies
        SDL_Texture* texturesZombie[3];

};