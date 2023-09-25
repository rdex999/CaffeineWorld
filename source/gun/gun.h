#ifndef GUN_H
#define GUN_H
#include "../base/base.h"
#include "../player/player.h"

class gun
{
    public:
        gun(base* baseObj, player* playerObj);
        ~gun();
    
    private:

        // store object pointers
        base* baseObj;
        player* playerObj;

        // the texture of the gun
        SDL_Texture* texture;
        
        // runs every frame 
        void tick(double deltaTime);

        // renders the gun
        void render();

        // the size of the gun image
        vector2d gunSize;

};

#endif