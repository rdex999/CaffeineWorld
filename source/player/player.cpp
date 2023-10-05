#include "player.h"

player::player(base *baseObj)
{
    // store the baseObj pointer
    this->baseObj = baseObj;

    screenBox = vector2d(baseObj->screenSize.X/5, baseObj->screenSize.Y/5,
        baseObj->screenSize.X - baseObj->screenSize.X/5, baseObj->screenSize.Y - baseObj->screenSize.Y/5);

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

    // walking speed
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
    screenLocation = baseObj->screenSize / 2;

    // set the player skin size
    screenLocation.W = 556/7;
    screenLocation.H = 1030/7;

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
    if((screenLocation - location).inBox(vector2d(screenBox.X, screenBox.Y), vector2d(screenBox.W, screenBox.H))){
        screenLocation -= location;
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
} 

void player::render()
{
    SDL_Rect rect = {screenLocation.X, screenLocation.Y, screenLocation.W, screenLocation.H};
    SDL_RenderCopyEx(baseObj->mainRenderer, textures[textureIndex], NULL, &rect, 0, NULL, SDL_RendererFlip(flip));
}
