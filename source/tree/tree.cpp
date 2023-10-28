#include "tree.h"

tree::tree(base *baseObj, player *playerObj, SDL_Texture *texture,
    const vector2d* location, tree** treeArray, int treeArrayIdx)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;
    this->texture = texture;
    this->location = *location;
    this->treeArray = treeArray;
    this->treeArrayIdx = treeArrayIdx;

    this->location.W = 396/1.3;
    this->location.H = 630/1.3;
}

tree::~tree()
{
    if(treeArray){
        treeArray[treeArrayIdx] = nullptr;
    }
}

void tree::tick()
{
    render();
}

void tree::render()
{
    SDL_Rect rect = {location.X, location.Y, location.W, location.H};
    SDL_RenderCopy(baseObj->mainRenderer, texture, NULL, &rect);
}