#include "entitysHead.h"
#define MAX_ENTITYS 10

entitysHead::entitysHead(base* baseObj, player* playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    // THE PLAYER TEXTURE IS JUST FOR DEVELOPMENT.
    // I WILL ADD A ZOMBIE TEXTURE IN THE FUTURE. 
    texturesZombie[0] = IMG_LoadTexture(baseObj->mainRenderer, "./images/zombie/zombieSkeletonStand-v3.0.png");
    if(!texturesZombie[0]){
        std::cout << "Error: could not create zombie texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    
    texturesZombie[1] = IMG_LoadTexture(baseObj->mainRenderer, "./images/zombie/zombieSkeletonWalking1-v3.0.png");
    if(!texturesZombie[1]){
        std::cout << "Error: could not create zombie walking 1 texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    
    texturesZombie[2] = IMG_LoadTexture(baseObj->mainRenderer, "./images/zombie/zombieSkeletonWalking1-v3.0.png");
    if(!texturesZombie[2]){
        std::cout << "Error: could not create zombie walking 2 texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    entityArray[0] = (entity*)(new zombie(baseObj, playerObj, entityArray, MAX_ENTITYS, 0, texturesZombie));
}

entitysHead::~entitysHead()
{
    for(int i=0; i<3; i++){
        if(texturesZombie[i]){
            SDL_DestroyTexture(texturesZombie[i]);
        }
    }

    for(int i=0; i<MAX_ENTITYS; i++){
        if(entityArray[i]){
            delete entityArray[i];
        }
    }
}

void entitysHead::tick()
{
    for(int i=0; i<MAX_ENTITYS; i++){
        if(entityArray[i]){
            entityArray[i]->location += baseObj->screenOffset;
            if(entityArray[i]->location.inBox(vector2d(0, 0), baseObj->screenSize) ||
                (entityArray[i]->location+vector2d(entityArray[i]->location.W, entityArray[i]->location.H)).
                inBox(vector2d(0, 0), baseObj->screenSize))
            {
                entityArray[i]->tick();
            } 
        }
    }
}
