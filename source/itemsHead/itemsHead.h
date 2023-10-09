#pragma once
#include "../attackHand/attackHand.h"
#include "../pickaxe/pickaxe.h"
#include "../gun/gun.h"

class itemsHead
{
    public:
        itemsHead(base* baseObj, player* playerObj);
        ~itemsHead();

        // runs every frame
        void tick();

        // store item pointers 
        pickaxe* pickaxeObj;
        attackHand* attackHandObj;
        gun* gunObj;
    
    private:

        // store baseObj and playerObj pointers
        base* baseObj;
        player* playerObj;


};