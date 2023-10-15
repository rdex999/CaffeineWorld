#include "zombie.h"

zombie::zombie(base *baseObj, player* playerObj, zombie** zombiesArray, int zombiesArrayLength,
    int zombieArrayIndex, SDL_Texture** textures)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->zombiesArray = zombiesArray;
    this->zombiesArrayLength = zombiesArrayLength;
    this->zombieArrayIndex = zombieArrayIndex;
    
    // for some reasone the c++ compiler wont let me do
    // this->textures = textures;
    this->textures[0] = textures[0];
    this->textures[1] = textures[1];
    this->textures[2] = textures[2];

    location = vector2d(baseObj->screenSize.X - baseObj->screenSize.X/4,
        baseObj->screenSize.Y/3, 0, 0);
}

zombie::~zombie()
{
    for(int i=0; i<3; i++){
        if(textures[i]){
            SDL_DestroyTexture(textures[i]);
        }
    }

    zombiesArray[zombieArrayIndex] = nullptr;
}

void zombie::tick()
{
    render();


}

void zombie::render()
{
    SDL_Rect rect = {location.X, location.Y, location.W, location.H};
    SDL_RenderCopyEx(baseObj->mainRenderer, textures[currentTextureIndex], NULL, &rect, 0, nullptr, SDL_RendererFlip(flip));
}
