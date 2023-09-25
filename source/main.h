#ifndef MAIN_H
#define MAIN_H
#include "base/base.h"
#include "background/background.h"
#include "player/player.h"
#include "inventory/inventory.h"
#include "gun/gun.h"
#include "attackHand/attackHand.h"

// container for all of the components
typedef struct container
{
    container();
    ~container();

    base* baseObj;
    background* backgroundObj;
    player* playerObj;
    inventory* inventoryObj;
    gun* gunObj;
    attackHand* attackHandObj;

    // handle keyboard
    void handleEvent();

    // runs all the tick functions from the boxes array 
    void runTicks();
} container;

#endif