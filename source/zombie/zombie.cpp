#include "zombie.h"
#define GRAVITY 9.80665
#define HIT_POWER 1.5
#define LIFEBAR_W (int)(87/1.3)
#define LIFEBAR_H (int)(18/1.3)
#define LIFE_REGEN 0.5
#define LIFE_REGEM_NORM_TIME 2 
#define LIFE_REGEN_TIME 5
#define DEMAGENUM_C 4 
#define DEMAGENUM_TIME 0.5

zombie::zombie(base *baseObj, player* playerObj, int zombieArrayIndex, vector2d* spawnLocation,
    SDL_Texture** textures, SDL_Texture* textureLifeBar)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
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
    life = 10;
    maxLife = life;
    wasHit = false;
    deltaHealthTime = 0;
    tookHitTime = 0;

    location = *spawnLocation;

    location.W = 154/3;
    location.H = 350/3;
}

zombie::~zombie()
{
    if(baseObj->entityArray){
        baseObj->entityArray[zombieArrayIndex] = nullptr;
    }

    for(int i=0; i<DEMAGENUM_C; i++){
        if(demageNums[i].texture){
            SDL_DestroyTexture(demageNums[i].texture);
        }
    }
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
        lastHitTime = 0;
        playerObj->takeDemage(HIT_POWER);
    }

    deltaHealthTime = std::clamp((double)0, (double)10, deltaHealthTime + baseObj->deltaTime);
    tookHitTime = std::clamp((double)0, (double)5, tookHitTime + baseObj->deltaTime);

    // if 5 seconds have passed since the zombie has taken a hit
    if(wasHit && deltaHealthTime >= LIFE_REGEN_TIME){
        wasHit = false;
        deltaHealthTime = 0;
        if(life <= maxLife - LIFE_REGEN){
            life += LIFE_REGEN;
        }else if(life < maxLife){
            life += maxLife - life; 
        }
    }

    if(life <= maxLife - LIFE_REGEN && deltaHealthTime >= LIFE_REGEM_NORM_TIME && !wasHit){
        deltaHealthTime = 0;
        life += LIFE_REGEN;
    }else if(life < maxLife && deltaHealthTime >= LIFE_REGEM_NORM_TIME && !wasHit){
        deltaHealthTime = 0;
        life += maxLife - life;
    }

}

void zombie::takeDemage(float demageAmount)
{
    if(tookHitTime >= 0.17){
        life -= demageAmount;
        wasHit = true;
        deltaHealthTime = 0;
        tookHitTime = 0;

        if(life <= 0){
            delete this;
        }
    
        for(int i=0; i<DEMAGENUM_C; i++){
            if(!(demageNums[i].texture)){

                demageNums[i].texture = text::createTextOutlineTexture(baseObj->mainRenderer,
                    "./fonts/Tilt_Warp/TiltWarp-Regular-VariableFont_XROT,YROT.ttf",
                    std::format("-{}", (int)demageAmount).c_str(),
                    SDL_Color(200, 0, 0), SDL_Color(50, 50, 50), 40, 3,
                    &demageNums[i].location.W, &demageNums[i].location.H);

                demageNums[i].rotation = 0;
                demageNums[i].time = 0;
                demageNums[i].direction = flip;
                demageNums[i].offset = 0;

                break;
            }
        }
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

        if(life / maxLife < 0.3){
            SDL_SetRenderDrawColor(baseObj->mainRenderer, 200, 0, 0, 0);
        }else if(life / maxLife < 0.5){
            SDL_SetRenderDrawColor(baseObj->mainRenderer, 200, 120, 0, 0);
        }else if(life / maxLife < 0.7){
            SDL_SetRenderDrawColor(baseObj->mainRenderer, 200, 200, 0, 0);
        }else if(life / maxLife < 0.9){
            SDL_SetRenderDrawColor(baseObj->mainRenderer, 0, 200, 0, 0);
        }

        SDL_RenderFillRect(baseObj->mainRenderer, &lifeBarRect);
    
        for(int i=0; i<DEMAGENUM_C; i++){
            demageNums[i].time += baseObj->deltaTime;
 
            if(demageNums[i].time >= DEMAGENUM_TIME){
                SDL_DestroyTexture(demageNums[i].texture);
                demageNums[i].texture = nullptr;
            }

            if(demageNums[i].texture){

                SDL_Rect demageRect = {0, (int)(location.Y - demageNums[i].location.H*1.5),
                    demageNums[i].location.W, demageNums[i].location.H};
                
                if(demageNums[i].direction){
                    demageNums[i].rotation -= baseObj->deltaTime * 100;
                    demageRect.x = location.X + location.W/2 - demageNums[i].location.W/2 - demageNums[i].offset;
                }else{
                    demageNums[i].rotation += baseObj->deltaTime * 100;
                    demageRect.x = location.X + location.W/2 - demageNums[i].location.W/2 + demageNums[i].offset;
                }
                
                SDL_RenderCopyEx(baseObj->mainRenderer, demageNums[i].texture, NULL, &demageRect,
                    demageNums[i].rotation, NULL, SDL_RendererFlip(false));
                
                demageNums[i].offset += baseObj->deltaTime * 100;

            }
        }
    }
}