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

        void setBox();

        vector2d screenLocation;
        vector2d playerSize;

        // function that runs on every fram
        void tick(double deltaTime);

        // the texture index to render
        int textureIndex;

        // sould the texture flip (for walking right or left) 
        bool flip;

        // function for walking. direction = -1 for right and direction = 1 for left 
        void walk(int direction);

        // walking speed
        float walkingSpeed;
};

#endif