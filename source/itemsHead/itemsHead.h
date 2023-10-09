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

    private:

        // store baseObj and playerObj pointers
        base* baseObj;
        player* playerObj;

        // store item pointers 
        pickaxe* pickaxeObj;
        attackHand* attackHandObj;
        gun* gunObj;

};