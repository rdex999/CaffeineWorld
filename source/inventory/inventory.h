#ifndef INVENTORY_H
#define INVENTORY_H
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "../base/base.h"

class inventory
{
    public:
        inventory(base* baseObj);
        ~inventory();

        void selectItem(int itemNumber);

        // the current amount of items`
        int itemsCount;
    
        // the selected item number
        int selectedItem;
    
        // the index of the first box of the inventory in the boxes array
        int firstBoxIndex;
    
    private:
        base* baseObj;

        // runs on every frame
        void tick(double deltaTime);

        // updates the the inventory items boxes at the boxes array
        // backOrForward can only be 10 or 0
        // 10 is the amount of pixels between each item on the screen
        void setBox(int backOrForward);


        // the index of the highlight box
        int highlightBoxIndex;

        // the location of the first item on the screen
        vector2d firstItemScreenLocation;

        // the highlight on the selected item
        SDL_Texture* selectedItemHighLight;

        // the hand item texture
        SDL_Texture* textureHandItem;

        // the gun item frame texture
        SDL_Texture* textureGunItem;
};

#endif