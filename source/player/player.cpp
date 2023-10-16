#include "player.h"

player::player(base *baseObj)
{
    // store the baseObj pointer
    this->baseObj = baseObj;

    screenBox = vector2d(baseObj->screenSize.X/4, baseObj->screenSize.Y/4,
        baseObj->screenSize.X - baseObj->screenSize.X/4, baseObj->screenSize.Y - baseObj->screenSize.Y/4);

    // set the texture index
    textureIndex = 0;

    // if the player is blocked by a wall from the right
    blockedRight = false;

    // if the plaer is blocked by a wall from the left
    blockedLeft = false;

    // whether the player is in the air or not
    inAir = true;

    // sould the texture flip (for walking right or left)
    flip = false;

    // original walking speed
    walkingSpeedOrigin = 37.f;

    // walking speed (140 for debug)
    walkingSpeed = walkingSpeedOrigin;

    // the slow start/end of walking
    walkingSlowDown = 0.f;

    // the slow down speed of stopping to walk
    slowDownEndWalk = 0;

    // if the player stopped walking
    stoppedWalking = 0;

    // the time between each step animation
    walkStepTime = 0.f;

    // the gravity intensity on earth (from wikipedia)
    gravity = 9.80665;

    // the slow gravity at the start of falling
    gravitySlowDown = 1.f;

    // if the player should jump
    jump = false;

    // the jumping intensity
    jumpIntensity = 10;

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
        move(vector2d(0, baseObj->deltaTime * gravity * std::clamp(gravitySlowDown, 1.f, 15.f) * -4));
        gravitySlowDown += baseObj->deltaTime*50;
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

    // check if the player is outside screenBox and if so then move him out and set screenOffset
    if(!location.inBox(vector2d(screenBox.X, screenBox.Y), vector2d(screenBox.W, screenBox.H))){
        int difference = 0; 
        if(location.Y < screenBox.Y){
            difference = screenBox.Y-location.Y;
            location.Y += difference;
            baseObj->screenOffset.Y += difference;
        }else if(location.Y+location.H >= screenBox.H){
            difference = location.Y+location.H-screenBox.H;
            location.Y -= difference;
            baseObj->screenOffset.Y -= difference;
        }else if(location.X <= screenBox.X){
            difference =  screenBox.X-location.X;
            location.X += difference;
            baseObj->screenOffset -= difference;
        }else if(location.X+location.W >= screenBox.W){
            difference = location.X+location.W-screenBox.X;
            location.X -= difference;
            baseObj->screenOffset += difference;
        }
    }
}

void player::render()
{
    SDL_Rect rect = {location.X, location.Y, location.W, location.H};
    SDL_RenderCopyEx(baseObj->mainRenderer, textures[textureIndex], NULL, &rect, 0, NULL, SDL_RendererFlip(flip));
}
