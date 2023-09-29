#pragma once
#include <SDL2/SDL_image.h>
#include "../base/base.h"
#include "../dVector2d/dVector2d.h"

// a coffee cup that the player needs to collect
class coffeeCup
{
    public:

        // direction 0 for flying to the right, direction 1 for flying to the left
        coffeeCup(base* baseObj, bool direction, std::vector<box*>::iterator boxIterator,
            coffeeCup** coffeeCupArray = nullptr, int coffeeCupArrayIndex = 0);
        ~coffeeCup();

    
    private:

        // store baseObj pointer
        base* baseObj;

        // runs every frame
        void tick(double deltaTime);
        
        // renders the coffee cup texture to the screen
        void render();

        // the coffee cup texture
        SDL_Texture* texture;

        // the location of the coffee cup on te screen
        dVector2d screenLocation;

        // the coffee cup image size
        vector2d coffeeCupSize;

        // pointer to the coffee cup box
        box* boxPtr;

        // where the coffee cup should fly to
        dVector2d direction;

        // if there is a coffee cup array, then the coffee cup can mark itself as nullptr
        // and free the memory
        coffeeCup** coffeeCupArray;

        // the index of the coffeeCup in the cuffeeCupArray
        int coffeeCupArrayIndex;
};