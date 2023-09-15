#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include "../base/base.h"

class player
{
    public:
        player(base* baseObj);
        ~player();

        base* baseObj;

        // the player has some different textures (standing skin, reloading skin, etc..) so an array it is 
        std::array<SDL_Texture*, 1> textures;

        void setBox(int textureIndex);

        vector2d screenLocation;
        vector2d playerSize;

        void tick();
};

#endif