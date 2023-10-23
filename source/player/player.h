#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include <functional>
#include "../entity/entity.h"
#include "../dVector2d/dVector2d.h"
#include "../inventory/items/items.h"
#include "../item/item.h"

class player : public entity
{
    public:
        player(base* baseObj);
        ~player() override;

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

        // sents the current texture to the standing texture
        void setTextureStand();

        // deals demage to the player
        void takeDemage(float demageAmount) override;

        // the box on the screen that the player is in
        vector2d screenBox;

        // add the vector2d to the players location and does cheking with the screenBox
        void move(vector2d location);
        void move(vector2d* location);

        // the index of the selected item in the itemArray
        int selectedItemIndex;
        
        // function that runs on every frame
        void tick() override;
    
        // the items array. each item has an item id (int)
        item* items[INVENTORY_CAPACITY] = {nullptr};

        // if the player was hit (by a zombie or something)
        bool hasHit;

        // time between each health regeneration
        double deltaHealthTime;

        bool shouldReload;

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