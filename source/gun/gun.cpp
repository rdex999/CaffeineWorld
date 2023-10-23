#include "gun.h"

gun::gun(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    itemID = itemGun;
    countEvent = true;
    gunSize = vector2d(251, 130)/3;
    count = 0;
    textureCount = nullptr;
    textureLogo = nullptr;

    texture = IMG_LoadTexture(baseObj->mainRenderer, "./images/gun/gun.png");
    if(!texture){
        std::cout << "Error: could not load gun texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    textureBullet = IMG_LoadTexture(baseObj->mainRenderer, "./images/bullet/bullet.png");
    if(!textureBullet){
        std::cout << "Error: could not load bullet texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
}

gun::~gun()
{
    if(texture){SDL_DestroyTexture(texture);}
    if(textureBullet){SDL_DestroyTexture(textureBullet);}
    
    for(int i=0; i<16; i++){
        if(bullets[i]){
            delete bullets[i];
        }
    }
}

void gun::reload()
{
    count = 0;
    countEvent = true;
}

void gun::tick()
{
    render();

    vector2d gunLocation(playerObj->location.X,
        playerObj->location.Y + playerObj->location.H/2.7 + gunSize.Y/3);

    if(playerObj->shouldReload){
        playerObj->shouldReload = false;
        reload();
    }

    // handle shooting with the gun
    lastGunShotTime += baseObj->deltaTime;
    if(playerObj->items[playerObj->selectedItemIndex] &&
        playerObj->items[playerObj->selectedItemIndex]->itemID == itemGun &&
        baseObj->mouseState == 1 && lastGunShotTime >= 0.2)
    {
        bullets[count] = new bullet(baseObj, &gunLocation, playerObj->flip, textureBullet, bullets, count);
        countEvent = true;
        lastGunShotTime = 0;
        count++;
        
        if(count > 16){
            reload();
        }
    }
}

void gun::render()
{
    for(int i=0; i<16; i++){
        if(bullets[i]){
            bullets[i]->tick();
        } 
    }
    if(playerObj->items[playerObj->selectedItemIndex] &&
        playerObj->items[playerObj->selectedItemIndex]->itemID == itemGun)
    {

        SDL_Rect playerRect = {(int)playerObj->location.X,
            (int)(playerObj->location.Y+playerObj->location.H/2.7), (int)gunSize.X, (int)gunSize.Y};

        SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &playerRect,
            baseObj->rotationPlayerToMouse, NULL, SDL_RendererFlip(playerObj->flip));
    }
}