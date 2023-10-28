#pragma once
#include "../player/player.h"

class tree
{
    public:
        tree(base* baseObj, player* playerObj, SDL_Texture* texture,
            const vector2d* location, tree** treeArray, int treeArrayIdx);
        
        ~tree();

        // runs every frame
        void tick();
        
        // the location of the tree on the screen 
        vector2d location;

    private:

        // renders the tree to the screen
        void render();

        // allways store base pointer
        base* baseObj;
        player* playerObj;

        // the texture that will render to the screen
        SDL_Texture* texture;
        
        // an array of tree pointers 
        tree** treeArray;

        // the index of this tree in the trees array
        int treeArrayIdx;

};