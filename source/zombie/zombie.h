#pragma once
#include "../entity/entity.h"
#include "../player/player.h"

class zombie : public entity
{
    public:
        zombie(base* baseObj, player* playerObj, entity** entityArray, int zombiesArrayLength,
            int zombieArrayIndex, SDL_Texture** textures);

        ~zombie() override;

        // runs every frame
        void tick() override;

    private:

        // store playerObj pointer
        player* playerObj;

        // renders the zombie to the screen 
        void render() override;

        void doJump();

        // an array of textures pointers
        // index 0: standing texture
        // index 1: walking 1
        // index 2: walking 2
        SDL_Texture* textures[3];

        // the index of the texture to render
        int currentTextureIndex;

        // the zombies array
        entity** entityArray;

        // the length of the zombies array
        int zombiesArrayLength;

        // the index of this zombie in the zombies array
        int zombieArrayIndex;

};
