#include "treesHead.h"
#define MAX_TREES 300

treesHead::treesHead(base *baseObj, player *playerObj)
{
    this->baseObj = baseObj;
    this->playerObj = playerObj;

    textureTree = IMG_LoadTexture(baseObj->mainRenderer, "./images/trees/tree-v1.0.png");
    if(!textureTree){
        std::cerr << "Error, could not create tree texture." << std::endl;
        exit(1);
    }

    baseObj->trees = trees;
    baseObj->treeArrayLength = MAX_TREES;

    vector2d treeLoc(500, 600);
    trees[0] = new tree(baseObj, playerObj, textureTree, &treeLoc, 0);
}

treesHead::~treesHead()
{
    if(textureTree){SDL_DestroyTexture(textureTree);}

    for(int i=0; i < MAX_TREES; i++){
        if(trees[i]){
            delete trees[i];
        }
    }
}

void treesHead::tick()
{
    for(int i=0; i < MAX_TREES; i++){
        if(trees[i] &&
            (trees[i]->location.inBox(vector2d(0, 0), baseObj->screenSize) ||
            trees[i]->location.getWH().inBox(vector2d(0, 0), baseObj->screenSize)))
        {
            trees[i]->tick();
        }
    }
}