#pragma once
#include "../coffeeCup/coffeeCup.h"

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

        // the texture
        SDL_Texture* texture;

        SDL_Texture* textureCoffeeCup;

        // time since the last coffee cup spawn
        double timeCoffeeCupSpawn;
};