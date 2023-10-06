#include "inventory.h"
#define ITEM_SIZE 60
#define BULLETS_FONT_SIZE 18

inventory::inventory(base *baseObj, player* playerObj, gun* gunObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->gunObj = gunObj;

    itemsCount = 0;
    selectedItem = 1;

    playerObj->selectedItem = selectedItem;
    
    firstItemScreenLocation = vector2d(baseObj->screenSize.X/2 - (baseObj->screenSize.X/3)/2,
        baseObj->screenSize.Y - baseObj->screenSize.Y/15);

    highlightScreenLocation = firstItemScreenLocation;

    textureHandItem = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/handItem.png");
    if(!textureHandItem){
        std::cout << "Error: could not create the hand inventory frame texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    itemsCount++;

    textureGunItem = IMG_LoadTexture(baseObj->mainRenderer, "./images/inventory/gunItem-v1.2.png");
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
    if(textureHandItem){SDL_DestroyTexture(textureHandItem);}
    if(selectedItemHighLight){SDL_DestroyTexture(selectedItemHighLight);}
    if(textureGunItem){SDL_DestroyTexture(textureGunItem);}
    if(textureBulletsLeft){SDL_DestroyTexture(textureBulletsLeft);}
}

void inventory::selectItem(int itemNumber)
{
    if(selectedItem < itemNumber){
        selectedItem = itemNumber;
        playerObj->selectedItem = selectedItem;
        setBox(10 * (itemNumber - 1));
    }else if(selectedItem > itemNumber){
        selectedItem = itemNumber;
        playerObj->selectedItem = selectedItem;
        setBox(0);
    }
}

void inventory::setBox(int backOrForward)
{
    // change the highlight texture position.
    highlightScreenLocation.X = firstItemScreenLocation.X + (ITEM_SIZE * (selectedItem - 1)) + backOrForward;
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
    }
}

void inventory::render()
{
    SDL_Rect handRect = {(int)firstItemScreenLocation.X, (int)firstItemScreenLocation.Y, ITEM_SIZE, ITEM_SIZE};
    SDL_RenderCopy(baseObj->mainRenderer, textureHandItem, NULL, &handRect);

    SDL_Rect gunRect = {(int)firstItemScreenLocation.X + ITEM_SIZE + 10, (int)firstItemScreenLocation.Y, ITEM_SIZE, ITEM_SIZE};
    SDL_RenderCopy(baseObj->mainRenderer, textureGunItem, NULL, &gunRect);

    SDL_Rect bulletsLeftFontRect = {firstItemScreenLocation.X + ITEM_SIZE + BULLETS_FONT_SIZE,
        int(firstItemScreenLocation.Y + ITEM_SIZE - ITEM_SIZE/2.3), bulletsLeftFontSize.X,  bulletsLeftFontSize.Y};
    SDL_RenderCopy(baseObj->mainRenderer, textureBulletsLeft, NULL, &bulletsLeftFontRect);

    SDL_Rect highlightRect = {(int)highlightScreenLocation.X, (int)highlightScreenLocation.Y, ITEM_SIZE, ITEM_SIZE};
    SDL_RenderCopy(baseObj->mainRenderer, selectedItemHighLight, NULL, &highlightRect);
}