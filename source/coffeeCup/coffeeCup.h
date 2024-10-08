#pragma once
#include <SDL2/SDL_image.h>
#include "../base/base.h"
#include "../dVector2d/dVector2d.h"

// a coffee cup that the player needs to collect
class coffeeCup
{
    public:

        // direction 0 for flying to the right, direction 1 for flying to the left
        coffeeCup(base* baseObj, bool direction, SDL_Texture* texture,
            coffeeCup** coffeeCupArray = nullptr, int coffeeCupArrayIndex = 0);
        ~coffeeCup();
    
        // runs every frame
        void tick();
    
    private:

        // store baseObj pointer
        base* baseObj;
        
        // renders the coffee cup texture to the screen
        void render();

        // the coffee cup texture
        SDL_Texture* texture;

        // the location of the coffee cup on te screen
        dVector2d screenLocation;

        // the coffee cup image size
        vector2d coffeeCupSize;

        // where the coffee cup should fly to
        dVector2d direction;

        // if there is a coffee cup array, then the coffee cup can mark itself as nullptr
        // and free the memory
        coffeeCup** coffeeCupArray;

        // the index of the coffeeCup in the cuffeeCupArray
        int coffeeCupArrayIndex;

        // the speed that the coffeeCup moves in
        float speed;

        // time since the coffeeCup spawnd
        double runningTime;
};