#include "itemsHead.h"

itemsHead::itemsHead(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    attackHandObj = new attackHand(baseObj, playerObj);

    for(int i=0; i<INVENTORY_CAPACITY; i++){
        switch ((itemId)playerObj->items[i].itemID)
        {
        case itemWoodenPickaxe:
            pickaxeObj = new pickaxe(baseObj, playerObj, (itemId)playerObj->items[i].itemID);
            break;

        case itemGun:
            gunObj = new gun(baseObj, playerObj);
            break;

        default:
            break;
        }
    }
}

itemsHead::~itemsHead()
{
    if(attackHandObj){delete attackHandObj;}
    if(pickaxeObj){delete pickaxeObj;}
    if(gunObj){delete gunObj;}
}

void itemsHead::tick()
{
    switch (playerObj->selectedItem)
    {
    case ITEM_EMPTY:
        if(attackHandObj){
            attackHandObj->tick();
        }else{
            attackHandObj = new attackHand(baseObj, playerObj);
        }
        break;

    case itemWoodenPickaxe:
        if(pickaxeObj){
            pickaxeObj->tick();
        }else{
            pickaxeObj = new pickaxe(baseObj, playerObj, (itemId)playerObj->selectedItem);
        }
        break;

    case itemGun:
        if(gunObj){
            gunObj->tick();
        }else{
            gunObj = new gun(baseObj, playerObj);
        }

    default:
        break;
    }

}
