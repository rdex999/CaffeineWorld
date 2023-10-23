#include "item.h"

item::item(itemId itemID, int count, bool countEvent)
{
    this->itemID = itemID;
    this->count = count;
    this->countEvent = countEvent;

    textureLogo = nullptr;
    textureCount = nullptr;
}

item::~item()
{
    if(textureLogo){SDL_DestroyTexture(textureLogo);}
    if(textureCount){SDL_DestroyTexture(textureCount);}
}

void item::tick()
{
}