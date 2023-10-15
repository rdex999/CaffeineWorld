#include "entitysHead.h"
#define MAX_ZOMBIES 10

entitysHead::entitysHead(base* baseObj, player* playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    // THE PLAYER TEXTURE IS JUST FOR DEVELOPMENT.
    // I WILL ADD A ZOMBIE TEXTURE IN THE FUTURE. 
    texturesZombie[0] = IMG_LoadTexture(baseObj->mainRenderer, "./images/player/skin.png");
    if(!texturesZombie[0]){
        std::cout << "Error: could not create zombie texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    
    texturesZombie[1] = IMG_LoadTexture(baseObj->mainRenderer, "./images/player/skinWalking2.png");
    if(!texturesZombie[1]){
        std::cout << "Error: could not create zombie walking 1 texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    
    texturesZombie[2] = IMG_LoadTexture(baseObj->mainRenderer, "./images/player/skinWalking4.png");
    if(!texturesZombie[2]){
        std::cout << "Error: could not create zombie walking 2 texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    zombiesArray[0] = new zombie(baseObj, playerObj, zombiesArray, MAX_ZOMBIES, 0, texturesZombie);
}

entitysHead::~entitysHead()
{
    for(int i=0; i<3; i++){
        if(texturesZombie[i]){
            SDL_DestroyTexture(texturesZombie[i]);
        }
    }

    for(int i=0; i<MAX_ZOMBIES; i++){
        if(zombiesArray[i]){
            delete zombiesArray[i];
        }
    }
}

void entitysHead::tick()
{
    for(int i=0; i<MAX_ZOMBIES; i++){
        if(zombiesArray[i] && zombiesArray[i]->location.inBox(vector2d(0, 0), baseObj->screenSize)){
            zombiesArray[i]->tick();
        }
    }
}
