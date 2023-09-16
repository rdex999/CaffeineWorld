#include "player.h"

player::player(base *baseObj)
{
    // store the baseObj pointer
    this->baseObj = baseObj;

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

    baseObj->boxes.insert(baseObj->boxes.end(), new box(textures[0], screenLocation,
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
    baseObj->boxes[baseObj->boxes.size() - 1]->startPosition = screenLocation;
    baseObj->boxes[baseObj->boxes.size() - 1]->endPosition = playerSize;
    baseObj->boxes[baseObj->boxes.size() - 1]->texture = textures[textureIndex];
    baseObj->boxes[baseObj->boxes.size() - 1]->flip = flip;
}

void player::tick(double deltaTime)
{
    // allways update the box when using tick 
    setBox();

    if(stoppedWalking != 0){
        if(slowDownEndWalk <= 0){
            slowDownEndWalk = 1;
            stoppedWalking = 0;
        }
        slowDownEndWalk -= deltaTime * 1.7;
        slowDownEndWalk = std::clamp(slowDownEndWalk, 0.f, 1.f);
        screenLocation.X -= (int)(slowDownEndWalk * stoppedWalking * walkingSpeed * 15 * deltaTime);
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