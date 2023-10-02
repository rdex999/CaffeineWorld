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

        // an array of all dirt blocks in the world
        dirtBlock* dirtBlockArray[10] = {nullptr};

        // the index of the current dirtBlock to run its tick function
        int dirtBlockArrayIndex;

        // the textures of the dirt blcks.
        // index 0 is dirt texture, index 1 is dirtGrass texture
        SDL_Texture* texturesDirtBlock[2];
};