#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include <functional>
#include "../base/base.h"
#include "../dVector2d/dVector2d.h"

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

        // sould the texture flip (for walking right or left) 
        bool flip;

        // the selected item 
        int selectedItem;
        // function that runs on every frame
        void tick();
    
        // whether the player is in the air or not
        bool inAir;

        // the slow gravity at the start of falling
        float gravitySlowDown;

        // if the player is blocked by a wall from the right
        bool blockedRight;


    private: 

        // renders the player
        void render();

        // baseObj pointer 
        base* baseObj;

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

        // the time between each step animation
        double walkStepTime;
};