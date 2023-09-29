#pragma once
#include <SDL2/SDL_image.h>
#include "../base/base.h"
#include "../dVector2d/dVector2d.h"

class coffeeCup
{
    public:
        coffeeCup(base* baseObj);
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
};