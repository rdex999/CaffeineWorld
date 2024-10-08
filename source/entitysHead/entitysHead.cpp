#include "entitysHead.h"
#define MAX_ENTITYS 10

entitysHead::entitysHead(base* baseObj, player* playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    texturesZombie[0] = IMG_LoadTexture(baseObj->mainRenderer, "./images/zombie/zombieSkeletonStand-v3.1.png");
    if(!texturesZombie[0]){
        std::cout << "Error: could not create zombie texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    
    texturesZombie[1] = IMG_LoadTexture(baseObj->mainRenderer, "./images/zombie/zombieSkeletonWalking1-v3.1.png");
    if(!texturesZombie[1]){
        std::cout << "Error: could not create zombie walking 1 texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    
    texturesZombie[2] = IMG_LoadTexture(baseObj->mainRenderer, "./images/zombie/zombieSkeletonWalking1-v3.1.png");
    if(!texturesZombie[2]){
        std::cout << "Error: could not create zombie walking 2 texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    textureMobLifeBar = IMG_LoadTexture(baseObj->mainRenderer, "./images/mobs/mobLifeBar/mobLifeBar-v1.1.png");
    if(!textureMobLifeBar){
        std::cout << "Error: could not create mob life bar texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    // spawns the zombies
    // i will change this in the future
    vector2d zombieSpawnLoc = vector2d(0, 500);
    for(int i=0; i<MAX_ENTITYS; i++){
        entityArray[i] = (entity*) (new zombie(baseObj, playerObj, i, &zombieSpawnLoc, texturesZombie, textureMobLifeBar));
    
        zombieSpawnLoc.X += 400; 
    }
    baseObj->entityArray = entityArray;
    baseObj->entityArrayLength = MAX_ENTITYS;
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

    if(textureMobLifeBar){SDL_DestroyTexture(textureMobLifeBar);}
}

void entitysHead::tick()
{
    for(int i=0; i<MAX_ENTITYS; i++){
        if(entityArray[i]){
            if(entityArray[i]->location.inBox(vector2d(0, 0), baseObj->screenSize) ||
                (entityArray[i]->location+vector2d(entityArray[i]->location.W, entityArray[i]->location.H)).
                inBox(vector2d(0, 0), baseObj->screenSize))
            {
                entityArray[i]->tick();
            }

            entityArray[i]->inAir = true;
            entityArray[i]->blockedLeft = false;
            entityArray[i]->blockedRight = false;
        }
    }
}
