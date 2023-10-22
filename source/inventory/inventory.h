#pragma once
#include <format>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "../itemsHead/itemsHead.h"
#include "items/items.h"
#include "../text/text.h"

class inventory
{
    public:
        inventory(base* baseObj, player* playerObj, itemsHead* itemsHeadObj);
        ~inventory();

        // selects an item from the inventory
        void selectItem(int itemNumber);

        // offset can be 1 or -1
        void selectItemOffset(int offset);

        // runs on every frame
        void tick();
    
    private:
        base* baseObj;
        player* playerObj;
        itemsHead* itemsHeadObj;

        // renders all the inventory items
        void render();

        // the location of the first item on the screen
        vector2d firstItemScreenLocation;

        // the highlight texture screen location
        vector2d highlightScreenLocation;

        // the highlight on the selected item
        SDL_Texture* selectedItemHighLight;

        // the item frame texture
        SDL_Texture* textureItemFrame;
};