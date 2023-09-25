#include "inventory.h"

inventory::inventory(base *baseObj, player* playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    itemsCount = 0;
    selectedItem = 1;

    playerObj->selectedItem = selectedItem;
    
    firstItemScreenLocation = vector2d(baseObj->screenSize.X/2 - (baseObj->screenSize.X/3)/2,
        baseObj->screenSize.Y - baseObj->screenSize.Y/11);

    highlightScreenLocation = firstItemScreenLocation;

    textureHandItem = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/handItem.png");
    if(!textureHandItem){
        std::cout << "Error: could not create the hand inventory frame texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    itemsCount++;

    textureGunItem = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/gunItem.png");
    if(!textureGunItem){
        std::cout << "Error: could not create the gun inventory frame texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    itemsCount++;
 
    selectedItemHighLight = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/itemHighlight.png");
    if(!selectedItemHighLight){
        std::cout << "Error: could not create the item highlight texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    baseObj->boxes.insert(baseObj->boxes.end(), new box(std::bind(&inventory::render, this),
        std::bind(&inventory::tick, this, std::placeholders::_1)));
}

inventory::~inventory()
{
    if(textureHandItem){SDL_DestroyTexture(textureHandItem);}
    if(selectedItemHighLight){SDL_DestroyTexture(selectedItemHighLight);}
    if(textureGunItem){SDL_DestroyTexture(textureGunItem);}
}

void inventory::selectItem(int itemNumber)
{
    if(selectedItem < itemNumber){
        selectedItem = itemNumber;
        playerObj->selectedItem = selectedItem;
        setBox(10);
    }else if(selectedItem > itemNumber){
        selectedItem = itemNumber;
        playerObj->selectedItem = selectedItem;
        setBox(0);
    }
}

void inventory::setBox(int backOrForward)
{
    // change the highlight texture position.
    highlightScreenLocation.X = firstItemScreenLocation.X + (85 * (selectedItem - 1)) + backOrForward;
}

void inventory::tick(double deltaTime)
{

}

void inventory::render()
{
    SDL_Rect handRect = {firstItemScreenLocation.X, firstItemScreenLocation.Y, 85, 85};
    SDL_RenderCopy(baseObj->mainRenderer, textureHandItem, NULL, &handRect);

    SDL_Rect gunRect = {firstItemScreenLocation.X + 85 + 10, firstItemScreenLocation.Y, 85, 85};
    SDL_RenderCopy(baseObj->mainRenderer, textureGunItem, NULL, &gunRect);

    SDL_Rect highlightRect = {highlightScreenLocation.X, highlightScreenLocation.Y, 85, 85};
    SDL_RenderCopy(baseObj->mainRenderer, selectedItemHighLight, NULL, &highlightRect);
}