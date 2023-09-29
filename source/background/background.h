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

    private:

        // runs every frame
        void tick(double deltaTime);

        // renders the background and the coffee cupt 
        void render();

        // the baseObj pointer
        base* baseObj;

        // the texture
        SDL_Texture* texture;

        // store the background box pointer
        box* boxPtr;

        // time since the last coffee cup spawn
        double timeCoffeeCupSpawn;
};