#pragma once
#include <SDL2/SDL_image.h>
#include "../base/base.h"
#include "../player/player.h"

class attackHand
{
    public:
        attackHand(base* baseObj, player* playerObj);
        attackHand() = default;
        ~attackHand();

        // runs every frame
        void tick();
    
    private:

        // renders the hand object 
        void render();

        // store pointers
        base* baseObj;
        player* playerObj;

        // the hand texture
        SDL_Texture* texture;

        // the hand location on the screen
        vector2d screenLocation;

        // if the player is currently attacking (with the hand) 
        bool attack;

        // offset from the original hand point to the attack point(where the hand reaches to)
        double attackOffset;

        // the slow down at the end of the attack
        double attackSlowDown;

        // the rotation of the hand
        double rotation;

        dVector2d direction;
};