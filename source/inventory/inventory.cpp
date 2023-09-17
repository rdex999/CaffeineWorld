#include "inventory.h"

inventory::inventory(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    selectedItemHighLight = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/itemHighlight.png");
    if(!selectedItemHighLight){
        std::cout << "Error: could not create the item highlight texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    textureHandItem = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/handItem.png");
    if(!textureHandItem){
        std::cout << "Error: could not create the hand inventory frame texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    selectedItem = 1;

    firstItemScreenLocation = vector2d(baseObj->screenSize.X/2 - (baseObj->screenSize.X/3)/2,
        baseObj->screenSize.Y - baseObj->screenSize.Y/11);

    box* tempBoxPtr = new box(textureHandItem,
        firstItemScreenLocation,
        vector2d(85, 85));

    baseObj->boxes.insert(baseObj->boxes.end() - 1, tempBoxPtr);

    // get the index of tempBoxPtr in the boxes array
    firstBoxIndex = std::distance(baseObj->boxes.begin(), std::find(baseObj->boxes.begin(), baseObj->boxes.end(), tempBoxPtr));
    std::cout << firstBoxIndex << std::endl;

    textureGunItem = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/gunItem.png");
    if(!textureGunItem){
        std::cout << "Error: could not create the gun inventory frame texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    baseObj->boxes.insert(baseObj->boxes.end() - 1, new box(textureGunItem, firstItemScreenLocation+vector2d(95, 0),
        vector2d(85, 85)));

    baseObj->boxes.insert(baseObj->boxes.end() - 1, new box(selectedItemHighLight,
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

}

void inventory::tick(double deltaTime)
{

}