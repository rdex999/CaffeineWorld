#pragma once
#include <format>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "../base/base.h"
#include "../player/player.h"
#include "../gun/gun.h"

class inventory
{
    public:
        inventory(base* baseObj, player* playerObj, gun* gunObj);
        ~inventory();

        void selectItem(int itemNumber);

        // the selected item number
        int selectedItem;
    
        // runs on every frame
        void tick();
    
    private:
        base* baseObj;
        player* playerObj;
        gun* gunObj;

        // renders all the inventory items
        void render();

        // updates the the inventory items boxes at the boxes array
        // backOrForward can only be 10 or 0
        // 10 is the amount of pixels between each item on the screen
        void setBox(int backOrForward);

        // the location of the first item on the screen
        vector2d firstItemScreenLocation;

        // the highlight texture screen location
        vector2d highlightScreenLocation;

        // the width and height of the bullets left font texture
        vector2d bulletsLeftFontSize; 
        
        // the highlight on the selected item
        SDL_Texture* selectedItemHighLight;

        // the hand item texture
        SDL_Texture* textureHandItem;

        // the gun item frame texture
        SDL_Texture* textureGunItem;

        // the bullets left count texture
        SDL_Texture* textureBulletsLeft;
};