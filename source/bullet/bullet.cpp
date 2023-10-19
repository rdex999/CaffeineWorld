#include "bullet.h"
#define BULLET_DEMAGE 4

bullet::bullet(base *baseObj, vector2d *shootFrom, bool flip, SDL_Texture* texture, bullet** bullets, int bulletIndex)
{
    this->baseObj = baseObj;

    this->shootFrom = dVector2d(shootFrom->X, shootFrom->Y, (int)(1550/25), (int)(260/25));

    rotation = baseObj->rotationPlayerToMouse * (M_PI/180.f);

    this->flip = flip;

    speed = 110.f;

    this->bullets = bullets;

    this->bulletIndex = bulletIndex;

    this->texture = texture;
}

bullet::~bullet()
{
    if(bullets){
        bullets[bulletIndex] = nullptr;
    }
}

void bullet::tick()
{
    render();

    if(flip){
        shootFrom += dVector2d(std::cos(rotation) * baseObj->deltaTime * speed * 15,
            std::sin(rotation) * baseObj->deltaTime * speed * 15);
    }else{
        shootFrom -= dVector2d(std::cos(rotation) * baseObj->deltaTime * speed * 15,
            std::sin(rotation) * baseObj->deltaTime * speed * 15);
    } 
    if(!shootFrom.inBox(dVector2d(0, 0), dVector2d(baseObj->screenSize.X, baseObj->screenSize.Y))){
        delete this;
    }

    if(baseObj->entityArray){
        for(int i=0; i<baseObj->entityArrayLength; i++){
            if(baseObj->entityArray[i]){

                // if the bullet is inside the entities body
                if(shootFrom.inBox(dVector2d(baseObj->entityArray[i]->location.X, baseObj->entityArray[i]->location.Y),
                    dVector2d(baseObj->entityArray[i]->location.getWH().X, baseObj->entityArray[i]->location.getWH().Y)) || 
                    shootFrom.getWH().inBox(dVector2d(baseObj->entityArray[i]->location.X, baseObj->entityArray[i]->location.Y),
                    dVector2d(baseObj->entityArray[i]->location.getWH().X, baseObj->entityArray[i]->location.getWH().Y)))
                {
                    baseObj->entityArray[i]->takeDemage(BULLET_DEMAGE);
                    delete this;
                }
            }
        }
    }
}

void bullet::render()
{
    SDL_Rect rect = {(int)shootFrom.X, (int)shootFrom.Y, (int)shootFrom.W, (int)shootFrom.H};
    SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &rect, rotation * (180/M_PI), NULL, SDL_RendererFlip(flip));
}