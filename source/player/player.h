#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include "../base/base.h"
#include "../bullet/bullet.h"

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

        void setTextureStand();

        vector2d screenLocation;
        vector2d playerSize;

        // sould the texture flip (for walking right or left) 
        bool flip;

        // the selected item 
        int selectedItem;
    private: 
        // function that runs on every frame
        void tick(double deltaTime);

        // renders the player
        void render();

        // baseObj pointer 
        base* baseObj;

        // the index of the player box in the array
        int boxIndex;

        // the texture index to render
        int textureIndex;

        // the player has some different textures (standing skin, reloading skin, etc..) so an array it is 
        std::array<SDL_Texture*, 3> textures;

        // the slow down speed of stopping to walk
        float slowDownEndWalk;
        
        // walking speed
        float walkingSpeed;
        
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

        // the time between each step animation
        double walkStepTime;

        // the player box pointer
        box* boxPtr;

};

#endif