#include "player.h"
#define LIFE_REGEN 0.5
#define LIFE_REGEM_NORM_TIME 2 
#define LIFE_REGEN_TIME 5

player::player(base *baseObj)
{
    // store the baseObj pointer
    this->baseObj = baseObj;

    screenBox = vector2d(baseObj->screenSize.X/4, baseObj->screenSize.Y/4,
        baseObj->screenSize.X - baseObj->screenSize.X/4, baseObj->screenSize.Y - baseObj->screenSize.Y/4);

    items[0].itemID = itemWoodenPickaxe;
    items[1].itemID = itemGun;
    selectedItem = items[0].itemID;
    selectedItemIndex = 0;

    textureIndex = 0;
    blockedRight = false;
    blockedLeft = false;
    inAir = true;
    flip = false;
    walkingSpeedOrigin = 37.f;
    walkingSpeed = walkingSpeedOrigin;
    walkingSlowDown = 0.f;
    slowDownEndWalk = 0;
    stoppedWalking = 0;
    walkStepTime = 0.f;
    gravity = 9.80665;
    gravitySlowDown = 1.f;
    jump = false;
    jumpIntensity = 10;
    life = 10;
    maxLife = 10;
    hasHit = false;
    deltaHealthTime = 0;

    // the location of the floor in the background 
    floorLocation = vector2d(0, baseObj->screenSize.Y/1.064);

    // set the spawn location on screen
    location = baseObj->screenSize / 2 - vector2d(baseObj->screenSize.X/4, 0);

    // set the player skin size
    location.W = 556/9;
    location.H = 1030/9;

    // for the player-v3.0 
    //location.W = 240/3.85;
    //location.H = 435/3.85;

    // load the skin images
    textures[0] = IMG_LoadTexture(baseObj->mainRenderer, "./images/player/skin.png");
    if(!textures[0]){
        std::cout << "Error: could not create skin texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    
    textures[1] = IMG_LoadTexture(baseObj->mainRenderer, "./images/player/skinWalking2.png");
    if(!textures[1]){
        std::cout << "Error: could not create skin walking 2 texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    
    textures[2] = IMG_LoadTexture(baseObj->mainRenderer, "./images/player/skinWalking4.png");
    if(!textures[2]){
        std::cout << "Error: could not create skin walking 4 texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
}

player::~player()
{
    for(SDL_Texture* texture: textures){
        if(texture){
            SDL_DestroyTexture(texture);
        }
    }

    for(int i=0; i<INVENTORY_CAPACITY; i++){
        if(items[i].textureCount){
            SDL_DestroyTexture(items[i].textureCount);
        }
        if(items[i].texture){
            SDL_DestroyTexture(items[i].texture);
        }
    }
}

void player::doJump()
{
    if(!jump && !inAir){
        jump = true;
        inAir = true;
    }
}

void player::setTextureStand()
{
    textureIndex = 0;
}

void player::takeDemage(float demageAmount)
{

    life = life - demageAmount > 0 ? life - demageAmount : 0;
    hasHit = true;
    deltaHealthTime = 0;
}

void player::move(vector2d location)
{
    if((this->location - location).inBox(vector2d(screenBox.X, screenBox.Y), vector2d(screenBox.W, screenBox.H)) &&
        (this->location+vector2d(this->location.W, this->location.H)-location).inBox(vector2d(screenBox.X, screenBox.Y),
        vector2d(screenBox.W, screenBox.H)))
    {
        this->location -= location;
    }else{
        baseObj->screenOffset += location;
    }
}

void player::move(vector2d *location)
{
}

void player::walk(int direction)
{
    if(direction == -1){
        flip = true;
        blockedLeft = false;
    }
    if(direction == 1){
        flip = false;
        blockedRight = false;
    }

    // make starting walking smooth 
    walkingSlowDown = std::clamp((float)(walkingSlowDown + baseObj->deltaTime * 1.5), 0.2f, 1.f);

    // the walking animation
    if(walkStepTime >= 0.4f){
        walkStepTime = 0.f;
    }else if(walkStepTime >= 0.2f){
        textureIndex = 2;
    }else if(walkStepTime >= 0.f){
        textureIndex = 1;
    }
    walkStepTime += baseObj->deltaTime;

    if(blockedLeft || blockedRight){
        direction = 0;
    }
    slowDownEndWalk = std::clamp(slowDownEndWalk + baseObj->deltaTime * 1.7, (double)0, (double)1);
    stoppedWalking = 0;
    // set the location
    move(vector2d((int)(baseObj->deltaTime * walkingSpeed * 15 * direction * walkingSlowDown), 0));
}

void player::tick()
{
    render();

    if(flip){
        baseObj->rotationPlayerToMouse = atan2(baseObj->mouseLocation.Y -
            (int)(location.Y+location.H/2.7),
            baseObj->mouseLocation.X - location.X)*180/M_PI;
    }else{
        baseObj->rotationPlayerToMouse = atan2(baseObj->mouseLocation.Y*-1 -
            (int)(location.Y+location.H/2.7)*-1,
            baseObj->mouseLocation.X*-1 - location.X*-1)*180/M_PI;
    }

    // slow stop when the player stops walking
    if(stoppedWalking != 0){
        if(slowDownEndWalk <= 0){
            stoppedWalking = 0;
        }
        if(blockedRight || blockedLeft){
            stoppedWalking = 0;
            slowDownEndWalk = 0;
        }

        slowDownEndWalk = std::clamp(slowDownEndWalk - baseObj->deltaTime * 1.7, (double)0, (double)1);
        move(vector2d((int)(slowDownEndWalk * stoppedWalking * walkingSpeed * 15 * baseObj->deltaTime), 0));
    }
    
    // if the player is above the floor and hes not jumping then use gravity 
    if(inAir && !jump){
        move(vector2d(0, baseObj->deltaTime * gravity * std::clamp(gravitySlowDown, 1.f, 11.f) * -7.5));
        gravitySlowDown += baseObj->deltaTime * gravity * 2.f;
    }

    // if the player wants to jump and he is not in the air then jump
    if(jump){
        move(vector2d(0, baseObj->deltaTime * std::clamp(jumpIntensity, -11.f, 10.f) * gravity * 7.5f));
        jumpIntensity -= baseObj->deltaTime * gravity * 2.f;
        if(!inAir){
            jump = false;
            jumpIntensity = 10;
        }
    }

    deltaHealthTime = std::clamp((double)0, (double)10, deltaHealthTime + baseObj->deltaTime);

    // if the player was hit, and three seconds have passed since
    if(hasHit && deltaHealthTime >= LIFE_REGEN_TIME){
        hasHit = false;
        deltaHealthTime = 0;
        if(life <= maxLife - LIFE_REGEN){
            life += LIFE_REGEN;
        }else if(life < maxLife){
            life += maxLife - life; 
        }
    }

    if(life <= maxLife - LIFE_REGEN && deltaHealthTime >= LIFE_REGEM_NORM_TIME && !hasHit){
        deltaHealthTime = 0;
        life += LIFE_REGEN;
    }else if(life < maxLife && deltaHealthTime >= LIFE_REGEM_NORM_TIME && !hasHit){
        deltaHealthTime = 0;
        life += maxLife - life;
    }

    // check if the player is outside screenBox and if so then move him out and set screenOffset
    if(!location.inBox(screenBox, vector2d(screenBox.W, screenBox.H)) ||
        !(location + vector2d(location.W, location.H)).inBox(screenBox, vector2d(screenBox.W, screenBox.H)))
    {
        if(location.Y < screenBox.Y){
            location.Y += screenBox.Y-location.Y;
        }else if(location.Y+location.H >= screenBox.H){
            location.Y -= location.Y+location.H-screenBox.H;
        }else if(location.X <= screenBox.X){
            location.X += screenBox.X-location.X;
        }else if(location.X+location.W >= screenBox.W){
            location.X -= location.X+location.W-screenBox.W;
        }
    }
}

void player::render()
{
    SDL_Rect rect = {location.X, location.Y, location.W, location.H};
    SDL_RenderCopyEx(baseObj->mainRenderer, textures[textureIndex], NULL, &rect, 0, NULL, SDL_RendererFlip(flip));
}
