#pragma once
#include "../coffeeCup/coffeeCup.h"
#include "../dirtBlock/dirtBlock.h"

class background
{
    public:
        background(base* baseObj);
        ~background();

        // an array of coffee cup pointers
        coffeeCup* coffeeCupArray[10] = {nullptr};

        // the current coffee cup index in the coffeeCupArray
        int currentCoffeeCupIndex;
        
        // runs every frame
        void tick();

    private:

        // renders the background and the coffee cupt 
        void render();

        // the baseObj pointer
        base* baseObj;

        // the background texture
        SDL_Texture* texture;

        // the texture of the coffee cup
        SDL_Texture* textureCoffeeCup;

        // time since the last coffee cup spawn
        double timeCoffeeCupSpawn;
};