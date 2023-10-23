#pragma once
#include "../base/base.h"
#include "../inventory/items/items.h"

class item
{
    public:
        item(itemId itemID, int count, bool countEvent);
        item() = default;
        virtual ~item();

        virtual void tick();

        // the id of the item 
        itemId itemID;
        
        // the amount of this item 
        int count;
        
        // if there was a change in the 'count' variable.
        // used to determin whether to update textureCount 
        bool countEvent;
        
        // the texture of the item in the inventory 
        SDL_Texture* textureLogo = nullptr;
        
        // the texture of the count text in the inventory 
        SDL_Texture* textureCount = nullptr;
        
        // the size of the count text 
        vector2d countSize = vector2d(0, 0);
};