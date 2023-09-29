#pragma once
#define MAX_COFFEECUP_SPAWN 10
#include "../coffeeCup/coffeeCup.h"

class background
{
    public:
        background(base* baseObj);
        ~background();

        // an array of coffee cup pointers
        coffeeCup* coffeeCupArray[MAX_COFFEECUP_SPAWN] = {nullptr};

    private:

        // runs every frame
        void tick(double deltaTime);

        // renders the background and the coffee cupt 
        void render();

        // the baseObj pointer
        base* baseObj;

        // the texture
        SDL_Texture* texture;
};