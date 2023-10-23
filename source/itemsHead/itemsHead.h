#pragma once
#include "../attackHand/attackHand.h"
#include "../pickaxe/pickaxe.h"
#include "../gun/gun.h"
#include "../inventory/items/items.h"

class itemsHead
{
    public:
        itemsHead(base* baseObj, player* playerObj);
        ~itemsHead();

        // runs every frame
        void tick();

        // store attack hand pointer
        attackHand* attackHandObj = nullptr;
    
    private:

        // store baseObj and playerObj pointers
        base* baseObj;
        player* playerObj;
};