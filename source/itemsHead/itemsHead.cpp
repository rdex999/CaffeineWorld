#include "itemsHead.h"

itemsHead::itemsHead(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    attackHandObj = new attackHand(baseObj, playerObj);
    pickaxeObj = new pickaxe(baseObj, playerObj, 1);
    gunObj = new gun(baseObj, playerObj);
}

itemsHead::~itemsHead()
{
    if(attackHandObj){delete attackHandObj;}
    if(gunObj){delete gunObj;}
}

void itemsHead::tick()
{
    switch (playerObj->selectedItem)
    {
    case -1:
    case 0:
        attackHandObj->tick();
        break;

    case 1:
        pickaxeObj->tick();
        break;

    default:
        break;
    }

    // allways run it because of the bullets
    gunObj->tick();
}
