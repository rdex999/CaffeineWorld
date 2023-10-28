#pragma once
#include "../base/base.h"
#include "../background/background.h"
#include "../player/player.h"
#include "../inventory/inventory.h"
#include "../gun/gun.h"
#include "../attackHand/attackHand.h"
#include "../blocksHead/blocksHead.h"
#include "../itemsHead/itemsHead.h"
#include "../entitysHead/entitysHead.h"
#include "../worldUI/worldUI.h"
#include "../treesHead/treesHead.h"

// container for all of the components
typedef struct container
{
    container();
    ~container();

    // handle keyboard
    void handleEvent();

    // runs all the tick functions from the boxes array 
    void runTicks();

    // adds the screenOffset to all classes that tick before the player
    void addOffset();

    base* baseObj;
    background* backgroundObj;
    player* playerObj;
    treesHead* treesHeadObj;
    itemsHead* itemsHeadObj;
    entitysHead* entitysHeadObj;
    inventory* inventoryObj;
    blocksHead* blocksHeadObj;
    worldUI* worldUiObj;

} container;