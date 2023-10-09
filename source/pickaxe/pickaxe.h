#pragma once
#include "../base/base.h"
#include "../player/player.h"

class pickaxe
{
    public:
        pickaxe(base* baseObj, player* playerObj, int itemNum);
        ~pickaxe();

        // runs every frame
        void tick();

    private:

        // store baseObj and playerObj pointers
        base* baseObj;
        player* playerObj;

        // renders the pickaxe to the screen
        void render();

        // the location of the pickaxe on the screen
        vector2d screenLocation;

        // the texture of the pickaxe 
        SDL_Texture* texture;

        // the rotation (in degrees) of the pickaxe
        int rotation;

        // if the player 'mined' (left click while the pickaxe is selected)
        bool mined;

        // the item number of the pickaxe.
        // since this is a pickaxe it can only be
        // 1 = wooden pickaxe
        // (add in future)
        int itemNum;

        // the pickaxe durability
        int pickaxeLife;

        int pickaxePower;
};