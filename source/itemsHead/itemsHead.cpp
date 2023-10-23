#include "itemsHead.h"

itemsHead::itemsHead(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    attackHandObj = new attackHand(baseObj, playerObj);

    playerObj->items[0] = new pickaxe(baseObj, playerObj, itemWoodenPickaxe);
    playerObj->items[1] = new gun(baseObj, playerObj);
}

itemsHead::~itemsHead()
{
    if(attackHandObj){delete attackHandObj;}
}

void itemsHead::tick()
{
    if(playerObj->selectedItemIndex != -1){
        if(playerObj->items[playerObj->selectedItemIndex]){
            playerObj->items[playerObj->selectedItemIndex]->tick();
        }else{
            if(attackHandObj){
                attackHandObj->tick();
            }else{
                attackHandObj = new attackHand(baseObj, playerObj);
            }    
        }
    }else{
        if(attackHandObj){
            attackHandObj->tick();
        }else{
            attackHandObj = new attackHand(baseObj, playerObj);
        }
    }
}
