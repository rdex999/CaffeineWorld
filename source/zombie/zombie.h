#pragma once
#include "../player/player.h"

class zombie : public entity
{
    public:
        zombie(base* baseObj, player* playerObj, int zombieArrayIndex, vector2d* spawnLocation,
            SDL_Texture** textures, SDL_Texture* textureLifeBar);

        ~zombie() override;

        // runs every frame
        void tick() override;

        // deals demage to the zombie
        void takeDemage(float demageAmount) override;

    private:

        // store playerObj pointer
        player* playerObj;

        // renders the zombie to the screen 
        void render() override;

        void doJump();

        // -1 for right 1 for left
        void walk(int direction);

        // an array of textures pointers
        // index 0: standing texture
        // index 1: walking 1
        // index 2: walking 2
        SDL_Texture* textures[3];

        // the texture of the life bar
        SDL_Texture* textureLifeBar;

        // the texture of the number that shows up when the player hits the zombie
        SDL_Texture* textureDemageNum;

        // the index of the texture to render
        int currentTextureIndex;

        // the index of this zombie in the zombies array
        int zombieArrayIndex;

        // time between each step
        double walkStepTime;

        // time since the last zombie hit
        double lastHitTime;

        // if the zombie has taken a hit
        bool wasHit;

        // time between each health regeneration
        double deltaHealthTime;

        // time since the last time the zombie has taken a hit
        double tookHitTime;
};
