#include "player.h"

player::player(base *baseObj)
{
    // store the baseObj pointer
    this->baseObj = baseObj;

    // set the texture index
    textureIndex = 0;

    // sould the texture flip (for walking right or left)
    flip = false;

    walkingSpeed = 20.f;

    // set the spawn location on screen
    screenLocation.X = baseObj->screenSize.X / 2;
    screenLocation.Y = baseObj->screenSize.Y / 2;

    // set the player skin size
    playerSize = vector2d(422, 420)/2;

    // load the skin images
    SDL_Surface* tempSurface = IMG_Load("./images/player/skin.png");
    if(!tempSurface){
        std::cout << "Error: could not load skin image.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    textures[0] = SDL_CreateTextureFromSurface(this->baseObj->mainRenderer, tempSurface);
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
    setBox();
    
}

void player::walk(int direction)
{
    if(direction == -1){flip = true;}
    if(direction == 1){flip = false;}

    screenLocation.X += (int)(baseObj->deltaTime * walkingSpeed * -15 * direction);
}