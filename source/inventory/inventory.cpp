#include "inventory.h"
#define ITEM_SIZE 60
#define BULLETS_FONT_SIZE 18

inventory::inventory(base *baseObj, player* playerObj, gun* gunObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->gunObj = gunObj;

    items[0] = 1;
    items[1] = 10;
    
    selectedItemIndex = 0;
    playerObj->selectedItem = items[0];


    firstItemScreenLocation = vector2d(baseObj->screenSize.X/2 - (baseObj->screenSize.X/3)/2,
        baseObj->screenSize.Y - baseObj->screenSize.Y/15);

    highlightScreenLocation = firstItemScreenLocation;

    textureItemFrame = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/itemFrame.png");
    if(!textureItemFrame){
        std::cout << "Error: could not create the item frame texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    textureWoodenPickaxeItem = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/woodenPickaxeItem.png");
    if(!textureWoodenPickaxeItem){
        std::cout << "Error: could not create the hand item texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    selectedItemHighLight = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/itemHighlight.png");
    if(!selectedItemHighLight){
        std::cout << "Error: could not create the item highlight texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    textureGunItem = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/gunItem.png");
    if(!textureGunItem){
        std::cout << "Error: could not create the gun item texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    textureBulletsLeft = baseObj->createTextTexture("./fonts/Tilt_Warp/TiltWarp-Regular-VariableFont_XROT,YROT.ttf",
        std::format("{}/16", 16-gunObj->currentBullet).c_str(), SDL_Color(255, 255, 255), BULLETS_FONT_SIZE,
        &bulletsLeftFontSize.X, &bulletsLeftFontSize.Y);
    if(!textureBulletsLeft){
        std::cout << "Error: could not create bullets left font texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    
}

inventory::~inventory()
{
    if(selectedItemHighLight){SDL_DestroyTexture(selectedItemHighLight);}
    if(textureBulletsLeft){SDL_DestroyTexture(textureBulletsLeft);}
    if(textureItemFrame){SDL_DestroyTexture(textureItemFrame);}
    if(textureWoodenPickaxeItem){SDL_DestroyTexture(textureWoodenPickaxeItem);}
    if(textureGunItem){SDL_DestroyTexture(textureGunItem);}
}

void inventory::selectItem(int itemNumber)
{
    //if the player selects the same item, then unselect 
    if(itemNumber == selectedItemIndex+1){
        playerObj->selectedItem = -1;
        selectedItemIndex = -1; 
    }else{
        highlightScreenLocation.X = firstItemScreenLocation.X + ITEM_SIZE*(itemNumber-1) + 10*(itemNumber-1);
        playerObj->selectedItem = items[itemNumber-1];
        selectedItemIndex = itemNumber-1;
    }
}

void inventory::selectItemOffset(int offset)
{
    if(selectedItemIndex+offset+1 > 10){
        selectItem(1);
    }else if(selectedItemIndex+offset+1 < 1){
        selectItem(10);
    }else{
        // +1 because the index starts from zero and itemNumber(the argument) starts from 1
        selectItem(selectedItemIndex+offset+1);
    }
}

void inventory::tick()
{
    render();

    if(gunObj->gunShot){
        if(textureBulletsLeft){SDL_DestroyTexture(textureBulletsLeft);}
        textureBulletsLeft = baseObj->createTextTexture("./fonts/Tilt_Warp/TiltWarp-Regular-VariableFont_XROT,YROT.ttf",
            std::format("{}/16", 16-gunObj->currentBullet).c_str(), SDL_Color(255, 255, 255), BULLETS_FONT_SIZE,
            &bulletsLeftFontSize.X, &bulletsLeftFontSize.Y);
        
        if(!textureBulletsLeft){
            std::cout << "Error: could not update the bullets left font texture.\n" << SDL_GetError() << std::endl;
            exit(1);
        }
        std::cout << gunObj->gunShot << std::endl;
    }
}

void inventory::render()
{
    vector2d itemLocation = firstItemScreenLocation;
    for(int i=0; i<10; i++)
    {
        itemLocation.X = firstItemScreenLocation.X + ITEM_SIZE*i + 10*i;

        switch (items[i])
        {
            case 1:{
                SDL_Rect woodenPickaxeRect {itemLocation.X, itemLocation.Y, ITEM_SIZE, ITEM_SIZE};
                SDL_RenderCopy(baseObj->mainRenderer, textureWoodenPickaxeItem, NULL, &woodenPickaxeRect);
                break;
            }

            case 10:{
                SDL_Rect gunRect = {itemLocation.X, itemLocation.Y, ITEM_SIZE, ITEM_SIZE};
                SDL_RenderCopy(baseObj->mainRenderer, textureGunItem, NULL, &gunRect);

                SDL_Rect bulletsLeftRect = {(int)(itemLocation.X+bulletsLeftFontSize.X/4.8), 
                    (int)(itemLocation.Y+bulletsLeftFontSize.Y*1.5),
                    bulletsLeftFontSize.X, bulletsLeftFontSize.Y};
                SDL_RenderCopy(baseObj->mainRenderer, textureBulletsLeft, NULL, &bulletsLeftRect);
                break;
            }

            default:{
                break;
            }
        }

        SDL_Rect rect = {itemLocation.X, itemLocation.Y, ITEM_SIZE, ITEM_SIZE};
        SDL_RenderCopy(baseObj->mainRenderer, textureItemFrame, NULL, &rect);
    }

    if(selectedItemIndex != -1){
        SDL_Rect highlightRect = {highlightScreenLocation.X, highlightScreenLocation.Y, ITEM_SIZE, ITEM_SIZE};
        SDL_RenderCopy(baseObj->mainRenderer, selectedItemHighLight, NULL, &highlightRect);
    }
}