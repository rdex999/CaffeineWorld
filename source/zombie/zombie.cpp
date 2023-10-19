#include "zombie.h"
#define GRAVITY 9.80665
#define HIT_POWER 1.5
#define LIFEBAR_W (int)(87/1.3)
#define LIFEBAR_H (int)(18/1.3)

zombie::zombie(base *baseObj, player* playerObj, entity** entityArray, int zombiesArrayLength,
    int zombieArrayIndex, SDL_Texture** textures, SDL_Texture* textureLifeBar)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->entityArray = entityArray;
    this->zombiesArrayLength = zombiesArrayLength;
    this->zombieArrayIndex = zombieArrayIndex;
    this->textureLifeBar = textureLifeBar;

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
    jumpIntensity = 8;
    walkStepTime = 0;
    lastHitTime = 0;
    life = 8;
    maxLife = 10;

    location = vector2d(baseObj->screenSize.X - baseObj->screenSize.X/4,
        baseObj->screenSize.Y/3);

    location.W = 154/3;
    location.H = 350/3;
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

    // if the zombie is above the floor and hes not jumping then use gravity 
    if(inAir && !jump){
        location.Y -= baseObj->deltaTime * GRAVITY * std::clamp(gravitySlowDown, 1.f, 15.f) * -4;
        gravitySlowDown += baseObj->deltaTime*50;
    }

    if(jump){
        location.Y -= baseObj->deltaTime * std::clamp(jumpIntensity, -9.f, 8.f) * GRAVITY * 3.5f;
        jumpIntensity -= baseObj->deltaTime * GRAVITY * 3.f;
        if(!inAir){
            jump = false;
            jumpIntensity = 10;
        }
    }

    if(playerObj->location.X - location.X > -3 && playerObj->location.X - location.X < 3){
        currentTextureIndex = 0;
    }else if(playerObj->location.X - location.X > -3){
        walk(-1);
    }else if(playerObj->location.X - location.X < 3){
        walk(1);
    }

    if(blockedLeft || blockedRight){
        doJump();
    }

    lastHitTime += std::clamp((double)0, (double)10, baseObj->deltaTime);

    // if the hand of the zombie touches the player
    if(((location + vector2d(0, location.H/2)).inBox(playerObj->location, playerObj->location.getWH()) ||
        (location + vector2d(location.W, location.H/2)).inBox(playerObj->location, playerObj->location.getWH())) &&
        lastHitTime >= 1)
    {
        playerObj->life -= HIT_POWER;
        lastHitTime = 0;
        playerObj->hasHit = true;
        playerObj->deltaHealthTime = 0;
    }
}

void zombie::doJump()
{
    if(!jump && !inAir){
        jump = true;
        inAir = true;
    }
}

void zombie::walk(int direction)
{
    if(direction == -1){
        flip = true;
        blockedLeft = false;
    }
    if(direction == 1){
        flip = false;
        blockedRight = false;
    }

    // the walking animation
    if(walkStepTime >= 0.4f){
        walkStepTime = 0.f;
    }else if(walkStepTime >= 0.2f){
        currentTextureIndex = 2;
    }else if(walkStepTime >= 0.f){
        currentTextureIndex = 1;
    }
    walkStepTime += baseObj->deltaTime;

    if(blockedLeft || blockedRight){
        direction = 0;
    }
    
    // set the location
    location.X -= baseObj->deltaTime * 15 * 15 * direction;
}

void zombie::render()
{
    SDL_Rect rect = {location.X, location.Y, location.W, location.H};
    SDL_RenderCopyEx(baseObj->mainRenderer, textures[currentTextureIndex], NULL, &rect, 0, nullptr, SDL_RendererFlip(flip));

    if(life < maxLife){
        SDL_Rect lifeBarEmptyRect = {location.X - location.W/5, location.Y - location.H/5, LIFEBAR_W, LIFEBAR_H};
        SDL_RenderCopy(baseObj->mainRenderer, textureLifeBar, NULL, &lifeBarEmptyRect);
        
        SDL_Rect lifeBarRect = {location.X - location.W/5 + LIFEBAR_W/12, location.Y - location.H/5 + LIFEBAR_H / 3,
            (int)((LIFEBAR_W - (int)(LIFEBAR_W/6.5)) * (life / maxLife)), LIFEBAR_H - 2*(LIFEBAR_H/3)};

        SDL_SetRenderDrawColor(baseObj->mainRenderer, 200, 0, 0, 0);
        SDL_RenderFillRect(baseObj->mainRenderer, &lifeBarRect);
    }
}