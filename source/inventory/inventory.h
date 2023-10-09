#pragma once
#include <format>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "../itemsHead/itemsHead.h"

class inventory
{
    public:
        inventory(base* baseObj, player* playerObj, itemsHead* itemsHeadObj);
        ~inventory();

        // selects an item from the inventory
        void selectItem(int itemNumber);

        // offset can be 1 or -1
        void selectItemOffset(int offset);

        // the index of the selected item in the items array
        int selectedItemIndex; 
        
        // runs on every frame
        void tick();
    
    private:
        base* baseObj;
        player* playerObj;
        itemsHead* itemsHeadObj;

        // renders all the inventory items
        void render();

        // the array of items
        // 0 = no item
        // -1/0 = hand
        // 10 = gun
        // 1 pickaxe
        int items[10] = {0};

        // the location of the first item on the screen
        vector2d firstItemScreenLocation;

        // the highlight texture screen location
        vector2d highlightScreenLocation;

        // the width and height of the bullets left font texture
        vector2d bulletsLeftFontSize; 
        
        // the highlight on the selected item
        SDL_Texture* selectedItemHighLight;

        // the item frame texture
        SDL_Texture* textureItemFrame;

        // the texture of the hand item
        SDL_Texture* textureWoodenPickaxeItem;

        // the bullets left count texture
        SDL_Texture* textureBulletsLeft;

        // the texture of the gun item
        SDL_Texture* textureGunItem;

};