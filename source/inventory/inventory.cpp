#include "inventory.h"

inventory::inventory(base *baseObj)
{
    this->baseObj = baseObj;

    itemsCount = 0;
    selectedItem = 1;
    
    firstItemScreenLocation = vector2d(baseObj->screenSize.X/2 - (baseObj->screenSize.X/3)/2,
        baseObj->screenSize.Y - baseObj->screenSize.Y/11);

    textureHandItem = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/handItem.png");
    if(!textureHandItem){
        std::cout << "Error: could not create the hand inventory frame texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    box* tempBoxPtr = new box(textureHandItem,
        firstItemScreenLocation,
        vector2d(85, 85));
    baseObj->boxes.insert(baseObj->boxes.end(), tempBoxPtr);
    itemsCount++;

    // get the index of tempBoxPtr in the boxes array
    firstBoxIndex = std::distance(baseObj->boxes.begin(), std::find(baseObj->boxes.begin(), baseObj->boxes.end(), tempBoxPtr));

    textureGunItem = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/gunItem.png");
    if(!textureGunItem){
        std::cout << "Error: could not create the gun inventory frame texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    baseObj->boxes.insert(baseObj->boxes.end(), new box(textureGunItem, firstItemScreenLocation+vector2d(95, 0),
        vector2d(85, 85)));
    itemsCount++;
 
    selectedItemHighLight = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/itemHighlight.png");
    if(!selectedItemHighLight){
        std::cout << "Error: could not create the item highlight texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    baseObj->boxes.insert(baseObj->boxes.end(), new box(selectedItemHighLight,
        vector2d((baseObj->screenSize.X/2 - (baseObj->screenSize.X/3)/2)*selectedItem,
            baseObj->screenSize.Y - baseObj->screenSize.Y/11),
        vector2d(85, 85)));
}

inventory::~inventory()
{
    if(textureHandItem){SDL_DestroyTexture(textureHandItem);}
    if(selectedItemHighLight){SDL_DestroyTexture(selectedItemHighLight);}
    if(textureGunItem){SDL_DestroyTexture(textureGunItem);}
}

void inventory::selectItem(int itemNumber)
{
    selectedItem = itemNumber;
    setBox();
}

void inventory::setBox()
{
    // change the highlight texture position. -1 because the selectedItem counts from one and array count from 0
    baseObj->boxes[firstBoxIndex+selectedItem - 1]->startPosition.X = firstItemScreenLocation.X + 85 * selectedItem + 10;
}

void inventory::tick(double deltaTime)
{

}