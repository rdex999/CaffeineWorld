#include "bullet.h"

bullet::bullet(base *baseObj, vector2d *shootFrom, bool flip, SDL_Texture* texture, bullet** bullets, int bulletIndex)
{
    this->baseObj = baseObj;

    size = vector2d(1550, 260)/25;

    this->shootFrom = dVector2d(shootFrom->X, shootFrom->Y);

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
}

void bullet::render()
{
    SDL_Rect rect = {(int)shootFrom.X, (int)shootFrom.Y, size.X, size.Y};
    SDL_RenderCopyEx(baseObj->mainRenderer, texture, NULL, &rect, rotation * (180/M_PI), NULL, SDL_RendererFlip(flip));
}