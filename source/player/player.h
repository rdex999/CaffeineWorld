#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include <functional>
#include "../entity/entity.h"
#include "../dVector2d/dVector2d.h"
#include "../inventory/items/items.h"

class player : public entity
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

        // the box on the screen that the player is in
        vector2d screenBox;

        // add the vector2d to the players location and does cheking with the screenBox
        void move(vector2d location);
        void move(vector2d* location);

        // the selected item 
        unsigned char selectedItem;

        // the index of the selected item in the itemArray
        int selectedItemIndex;
        
        // function that runs on every frame
        void tick() override;
    
        // the slow gravity at the start of falling
        float gravitySlowDown;

        // if the player should jump
        bool jump;
        
        // jumping intensity
        float jumpIntensity;

        // the items array. each item has an item id (int)
        item items[INVENTORY_CAPACITY] = {0, 0, true};

        // the block that the player stands on
        vector2d standingBlock;

    private: 

        // renders the player
        void render() override;

        // the texture index to render
        int textureIndex;

        // the player has some different textures (standing skin, reloading skin, etc..) so an array it is 
        std::array<SDL_Texture*, 3> textures;

        // the slow down speed of stopping to walk
        double slowDownEndWalk;
        
        // walking speed
        float walkingSpeed;
        
        // the gravity intensity
        float gravity;

        // the floor location
        vector2d floorLocation;

        // the time between each step animation
        double walkStepTime;
};