#include "player.h"

player::player(base *baseObj, inventory* inventoryObj)
{
    // store the baseObj pointer
    this->baseObj = baseObj;

    // store the inventoryObj pointer
    this->inventoryObj = inventoryObj;    

    // set the texture index
    textureIndex = 0;

    // sould the texture flip (for walking right or left)
    flip = false;

    // original walking speed
    walkingSpeedOrigin = 37.f;

    // walking speed
    walkingSpeed = walkingSpeedOrigin;

    // the slow start/end of walking
    walkingSlowDown = 0.f;

    // the slow down speed of stopping to walk
    slowDownEndWalk = 1;

    // if the player stopped walking
    stoppedWalking = 0;

    // the gravity intensity on earth (from wikipedia)
    gravity = 9.80665;

    // if the player should jump
    jump = false;

    // the jumping intensity
    jumpIntensity = 10;
    
    floorLocation = vector2d(0, baseObj->screenSize.Y/1.332);

    // set the spawn location on screen
    screenLocation = baseObj->screenSize / 2;

    // set the player skin size
    playerSize = vector2d(422, 420)/2;

    // load the skin images
    textures[0] = IMG_LoadTexture(baseObj->mainRenderer, "./images/player/skin.png");
    if(!textures[0]){
        std::cout << "Error: could not create skin texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    // because the inventory has more than one box in the boxes array, and + 1 because there is also the highlight box
    // which doesnt count in the itemsCount
    baseObj->boxes.insert(baseObj->boxes.end() - (inventoryObj->itemsCount + 1), new box(textures[0], screenLocation,
        playerSize, true, std::bind(&player::tick, this, std::placeholders::_1)));
}

player::~player()
{
    for(SDL_Texture* texture: textures){
        if(texture){
            SDL_DestroyTexture(texture);
        }
    }
}

void player::setBox()
{
    // update box in the last position in the array
    // -1 for the last box in the array, and also the item count +1 because the highlight texture doesnt count
    baseObj->boxes[baseObj->boxes.size() - 1 - (inventoryObj->itemsCount + 1)]->startPosition = screenLocation;
    baseObj->boxes[baseObj->boxes.size() - 1 - (inventoryObj->itemsCount + 1)]->endPosition = playerSize;
    baseObj->boxes[baseObj->boxes.size() - 1 - (inventoryObj->itemsCount + 1)]->texture = textures[textureIndex];
    baseObj->boxes[baseObj->boxes.size() - 1 - (inventoryObj->itemsCount + 1)]->flip = flip;
}

bool player::inAir()
{
    return screenLocation.Y < floorLocation.Y;
}

void player::doJump()
{
    if(!jump){
        jump = true;
    }
}

void player::walk(int direction)
{
    if(direction == -1){flip = true;}
    if(direction == 1){flip = false;}

    // make starting walking smooth 
    walkingSlowDown += baseObj->deltaTime * 1.5;
    walkingSlowDown = std::clamp(walkingSlowDown, 0.2f, 1.f);

    // set the location
    screenLocation.X -= (int)(baseObj->deltaTime * walkingSpeed * 15 * direction * walkingSlowDown);
}

void player::tick(double deltaTime)
{
    // allways update the box when using tick 
    setBox();

    // slow stop when the player stops walking
    if(stoppedWalking != 0){
        if(slowDownEndWalk <= 0){
            slowDownEndWalk = 1;
            stoppedWalking = 0;
        }
        slowDownEndWalk -= deltaTime * 1.7;
        slowDownEndWalk = std::clamp(slowDownEndWalk, 0.f, 1.f);
        screenLocation.X -= (int)(slowDownEndWalk * stoppedWalking * walkingSpeed * 15 * deltaTime);
    }
    
    // if the player is above the floor and hes not jumping then use gravity 
    if(screenLocation.Y < floorLocation.Y && !jump){
        screenLocation.Y += deltaTime * gravity * 15 * 4;
    }

    // if the player is below the floor then take him up a bit
    if(screenLocation.Y > floorLocation.Y){
        screenLocation.Y -= 3 * deltaTime;
    }

    // if the player wants to jump and he is not in the air then jump
    if(jump){
        screenLocation.Y -= deltaTime * jumpIntensity * gravity * 7.5f;
        jumpIntensity -= deltaTime * gravity * 1.7;
        if(jumpIntensity <= -10){
            jump = false;
            jumpIntensity = 10;
        }
    }
}