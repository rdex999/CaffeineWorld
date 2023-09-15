#include "player.h"

player::player(base *baseObj)
{
    // store the baseObj pointer
    this->baseObj = baseObj;

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
        playerSize, true, std::bind(&player::tick, this)));
}

player::~player()
{
    for(SDL_Texture* texture: textures){
        if(texture){
            SDL_DestroyTexture(texture);
        }
    }
}

void player::setBox(int textureIndex)
{
    // update box in the last position in the array
    baseObj->boxes[baseObj->boxes.size() - 1] = new box(textures[textureIndex], screenLocation,
        screenLocation+playerSize, true, std::bind(&player::tick, this));
}

void player::tick()
{
    std::cout << "player tick called" << std::endl;
}