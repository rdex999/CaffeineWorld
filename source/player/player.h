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

        // function for walking. direction = -1 for right and direction = 1 for left 
        void walk(int direction);

        // the speed of the slow walking when starting/stopping to walk
        float walkingSlowDown;

        // if the player stopped walking. 0=false, -1 for right, 1 for left
        int stoppedWalking;

        // original walking speed
        float walkingSpeedOrigin;

        // checks if the player is in the air and if he is not then jump 
        void doJump();

    private: 
        // function that runs on every fram
        void tick(double deltaTime);
        
        // the texture index to render
        int textureIndex;
        base* baseObj;

        // the player has some different textures (standing skin, reloading skin, etc..) so an array it is 
        std::array<SDL_Texture*, 1> textures;

        // updates the players box at teh boxes array
        void setBox();

        vector2d screenLocation;
        vector2d playerSize;
       
        // the slow down speed of stopping to walk
        float slowDownEndWalk;
        
        // walking speed
        float walkingSpeed;
        
        // sould the texture flip (for walking right or left) 
        bool flip;

        // the gravity intensity
        float gravity;

        // the floor location
        vector2d floorLocation;

        // if the player should jump
        bool jump;
        
        // jumping intensity
        float jumpIntensity;

        // returns whether the player is in the air or not
        bool inAir();
};

#endif