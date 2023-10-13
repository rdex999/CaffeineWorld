#include "gun.h"

gun::gun(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

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

    gunShot = false;

    gunSize = vector2d(251, 130)/3;
    currentBullet = 0;
}

gun::~gun()
{
    if(texture){SDL_DestroyTexture(texture);}
    if(textureBullet){SDL_DestroyTexture(textureBullet);}
}

void gun::reload()
{
    currentBullet = 0;
    gunShot = true;
}

void gun::tick()
{
    render();

    vector2d gunLocation(playerObj->screenLocation.X,
        playerObj->screenLocation.Y + playerObj->screenLocation.H/2.7 + gunSize.Y/3);

    // handle shooting with the gun
    lastGunShotTime += baseObj->deltaTime;
    if(playerObj->selectedItem == itemGun && baseObj->mouseState == 1 && lastGunShotTime >= 0.2){
        bullets[currentBullet] = new bullet(baseObj, &gunLocation, playerObj->flip, textureBullet, bullets, currentBullet);
        gunShot = true;
        lastGunShotTime = 0;
        currentBullet++;
        
        if(currentBullet > 16){
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
    if(playerObj->selectedItem == itemGun){

        SDL_Rect playerRect = {(int)playerObj->screenLocation.X,
            (int)(playerObj->screenLocation.Y+playerObj->screenLocation.H/2.7), (int)gunSize.X, (int)gunSize.Y};

        SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &playerRect,
            baseObj->rotationPlayerToMouse, NULL, SDL_RendererFlip(playerObj->flip));
    }
}