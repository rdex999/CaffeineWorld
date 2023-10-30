#include "itemsHead.h"

itemsHead::itemsHead(base *baseObj, player *playerObj)
    : attackHandObj(attackHand(baseObj, playerObj))
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    playerObj->items[0] = new pickaxe(baseObj, playerObj, itemWoodenPickaxe);
    playerObj->items[1] = new gun(baseObj, playerObj);
}

itemsHead::~itemsHead()
{
    attackHandObj.~attackHand();
}

void itemsHead::tick()
{
    if(playerObj->selectedItemIndex != -1 && playerObj->items[playerObj->selectedItemIndex]){
        playerObj->items[playerObj->selectedItemIndex]->tick();
    }else{
        attackHandObj.tick();
    }
}
