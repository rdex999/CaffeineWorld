#include "inventory.h"
#define ITEM_SIZE 60
#define BULLETS_FONT_SIZE 18

inventory::inventory(base *baseObj, player* playerObj, itemsHead* itemsHeadObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->itemsHeadObj = itemsHeadObj;

    firstItemScreenLocation = vector2d(baseObj->screenSize.X/2 - (baseObj->screenSize.X/3)/2,
        baseObj->screenSize.Y - baseObj->screenSize.Y/15);

    highlightScreenLocation = firstItemScreenLocation;

    textureItemFrame = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/itemFrame.png");
    if(!textureItemFrame){
        std::cout << "Error: could not create the item frame texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    selectedItemHighLight = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/itemHighlight.png");
    if(!selectedItemHighLight){
        std::cout << "Error: could not create the item highlight texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
}

inventory::~inventory()
{
    if(selectedItemHighLight){SDL_DestroyTexture(selectedItemHighLight);}
    if(textureItemFrame){SDL_DestroyTexture(textureItemFrame);}
}

void inventory::selectItem(int itemNumber)
{
    //if the player selects the same item, then unselect 
    if(itemNumber == playerObj->selectedItemIndex+1){
        playerObj->selectedItemIndex = -1;
    }else{
        highlightScreenLocation.X = firstItemScreenLocation.X + ITEM_SIZE*(itemNumber-1) + 10*(itemNumber-1);
        playerObj->selectedItemIndex = itemNumber-1;
    }
}

void inventory::selectItemOffset(int offset)
{
    if(playerObj->selectedItemIndex+offset+1 > ITEM_BAR_CAPACITY){
        selectItem(1);
    }else if(playerObj->selectedItemIndex+offset+1 < 1){
        selectItem(ITEM_BAR_CAPACITY);
    }else{
        // +1 because the index starts from zero and itemNumber(the argument) starts from 1
        selectItem(playerObj->selectedItemIndex+offset+1);
    }
}

void inventory::tick()
{
    render();
}

void inventory::render()
{
    vector2d itemLocation = firstItemScreenLocation;
    for(int i=0; i<ITEM_BAR_CAPACITY; i++)
    {
        itemLocation.X = firstItemScreenLocation.X + ITEM_SIZE*i + 10*i;

        switch (playerObj->items[i].itemID)
        {
            case itemWoodenPickaxe:{
                if(!playerObj->items[i].texture){
                    playerObj->items[i].texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/woodenPickaxeItem.png");
                    if(!playerObj->items[i].texture){
                        std::cout << "Error: could not create the hand item texture.\n" << SDL_GetError() << std::endl;
                        exit(1);
                    }
                }

                SDL_Rect woodenPickaxeRect = {itemLocation.X, itemLocation.Y, ITEM_SIZE, ITEM_SIZE};
                SDL_RenderCopy(baseObj->mainRenderer, playerObj->items[i].texture, NULL, &woodenPickaxeRect);
                break;
            }

            case itemGun:{
                if(itemsHeadObj->gunObj->gunShot || playerObj->items[i].textureCount == nullptr){
                    itemsHeadObj->gunObj->gunShot = false; 

                    if(playerObj->items[i].textureCount){
                        SDL_DestroyTexture(playerObj->items[i].textureCount);
                        playerObj->items[i].textureCount = nullptr;
                    }

                    playerObj->items[i].textureCount = text::createTextTexture(baseObj->mainRenderer,
                        "./fonts/Tilt_Warp/TiltWarp-Regular-VariableFont_XROT,YROT.ttf",
                        std::format("{}/16", 16-itemsHeadObj->gunObj->currentBullet).c_str(),
                        SDL_Color(255, 255, 255), BULLETS_FONT_SIZE,
                        &playerObj->items[i].countSize.X, &playerObj->items[i].countSize.Y);

                    if(!playerObj->items[i].textureCount){
                        std::cout << "Error: could not update the bullets left font texture.\n" << SDL_GetError() << std::endl;
                        exit(1);
                    }
                }
                if(!playerObj->items[i].texture){
                    playerObj->items[i].texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/gunItem.png");
                    if(!playerObj->items[i].texture){
                        std::cout << "Error: could not create the gun item texture.\n" << SDL_GetError() << std::endl;
                        exit(1);
                    }
                }

                SDL_Rect gunRect = {itemLocation.X, itemLocation.Y, ITEM_SIZE, ITEM_SIZE};
                SDL_RenderCopy(baseObj->mainRenderer, playerObj->items[i].texture, NULL, &gunRect);

                SDL_Rect bulletsLeftRect = {(int)(itemLocation.X+ITEM_SIZE/2-playerObj->items[i].countSize.X/2),
                    (int)(itemLocation.Y+ITEM_SIZE/1.8), playerObj->items[i].countSize.X, playerObj->items[i].countSize.Y};

                SDL_RenderCopy(baseObj->mainRenderer, playerObj->items[i].textureCount, NULL, &bulletsLeftRect);
                break;
            }

            case itemGrassBlock:{

                if(!playerObj->items[i].texture){
                    playerObj->items[i].texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/grassBlockItem.png");
                    if(!playerObj->items[i].texture){
                        std::cout << "Error: could not create the grass item texture.\n" << SDL_GetError() << std::endl;
                        exit(1);
                    }
                }

                SDL_Rect dirtItemRect = {itemLocation.X, itemLocation.Y, ITEM_SIZE, ITEM_SIZE};
                SDL_RenderCopy(baseObj->mainRenderer, playerObj->items[i].texture, NULL, &dirtItemRect);

                if(playerObj->items[i].countEvent){
                    playerObj->items[i].countEvent = false;

                    if(playerObj->items[i].textureCount){
                        SDL_DestroyTexture(playerObj->items[i].textureCount);
                        playerObj->items[i].textureCount = nullptr; 
                    }
    
                    playerObj->items[i].textureCount = text::createTextTexture(baseObj->mainRenderer,
                        "./fonts/Tilt_Warp/TiltWarp-Regular-VariableFont_XROT,YROT.ttf",
                        std::format("{}", playerObj->items[i].count).c_str(), SDL_Color(255, 255, 255), BULLETS_FONT_SIZE,
                        &playerObj->items[i].countSize.X, &playerObj->items[i].countSize.Y);
                    
                    if(!playerObj->items[i].textureCount){
                        std::cout << "Error: could not create the grass item count texture.\n" << SDL_GetError() << std::endl;
                        exit(1);
                    }
                }

                SDL_Rect grassCountRect = {(int)(itemLocation.X+ITEM_SIZE/2-playerObj->items[i].countSize.X/2),
                    (int)(itemLocation.Y+ITEM_SIZE/1.35-playerObj->items[i].countSize.Y/2),
                    playerObj->items[i].countSize.X, playerObj->items[i].countSize.Y};

                SDL_RenderCopy(baseObj->mainRenderer, playerObj->items[i].textureCount, NULL, &grassCountRect);

                break;
            }

            default:{
                break;
            }
        }

        SDL_Rect rect = {itemLocation.X, itemLocation.Y, ITEM_SIZE, ITEM_SIZE};
        SDL_RenderCopy(baseObj->mainRenderer, textureItemFrame, NULL, &rect);
    }

    if(playerObj->selectedItemIndex != -1){
        SDL_Rect highlightRect = {highlightScreenLocation.X, highlightScreenLocation.Y, ITEM_SIZE, ITEM_SIZE};
        SDL_RenderCopy(baseObj->mainRenderer, selectedItemHighLight, NULL, &highlightRect);
    }
}