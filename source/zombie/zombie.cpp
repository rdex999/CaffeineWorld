#include "zombie.h"
#define GRAVITY 9.80665

zombie::zombie(base *baseObj, player* playerObj, entity** entityArray, int zombiesArrayLength,
    int zombieArrayIndex, SDL_Texture** textures)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->entityArray = entityArray;
    this->zombiesArrayLength = zombiesArrayLength;
    this->zombieArrayIndex = zombieArrayIndex;
    
    // for some reasone the c++ compiler wont let me do
    // this->textures = textures;
    this->textures[0] = textures[0];
    this->textures[1] = textures[1];
    this->textures[2] = textures[2];

    entityID = entityZombie;

    currentTextureIndex = 0;
    flip = false;
    gravitySlowDown = 1.f;
    inAir = true;
    jump = false;
    jumpIntensity = 10;

    location = vector2d(baseObj->screenSize.X - baseObj->screenSize.X/4,
        baseObj->screenSize.Y/3, 100, 100);
}

zombie::~zombie()
{
    for(int i=0; i<3; i++){
        if(textures[i]){
            SDL_DestroyTexture(textures[i]);
        }
    }

    entityArray[zombieArrayIndex] = nullptr;
}

void zombie::tick()
{
    render();
    location += baseObj->screenOffset;

    // if the zombie is above the floor and hes not jumping then use gravity 
    if(inAir && !jump){
        location.Y -= baseObj->deltaTime * GRAVITY * std::clamp(gravitySlowDown, 1.f, 15.f) * -4;
        gravitySlowDown += baseObj->deltaTime*50;
    }

    if(jump){
        location.Y -= baseObj->deltaTime * std::clamp(jumpIntensity, -11.f, 10.f) * GRAVITY * 7.5f;
        jumpIntensity -= baseObj->deltaTime * GRAVITY * 2.f;
        if(!inAir){
            jump = false;
            jumpIntensity = 10;
        }
    }


    inAir = true;
}

void zombie::render()
{
    SDL_Rect rect = {location.X, location.Y, location.W, location.H};
    SDL_RenderCopyEx(baseObj->mainRenderer, textures[currentTextureIndex], NULL, &rect, 0, nullptr, SDL_RendererFlip(flip));
}

void zombie::doJump()
{
    if(!jump && !inAir){
        jump = true;
        inAir = true;
    }
}