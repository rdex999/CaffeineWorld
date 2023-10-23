#pragma once
#include "../player/player.h"
#include "../item/item.h"

class pickaxe : public item
{
    public:
        pickaxe(base* baseObj, player* playerObj, itemId itemID);
        ~pickaxe() override;

        // runs every frame
        void tick() override;

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

        // the pickaxe durability
        int pickaxeLife;

        int pickaxePower;
};