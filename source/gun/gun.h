#ifndef GUN_H
#define GUN_H
#include "../base/base.h"
#include "../player/player.h"

class gun
{
    public:
        gun(base* baseObj, player* playerObj, inventory* inventoryObj);
        ~gun();
    
    private:

        // store object pointers
        base* baseObj;
        player* playerObj;
        inventory* inventoryObj;

        // the texture of the gun
        SDL_Texture* texture;
        
        // runs every frame 
        void tick(double deltaTime);

        // updates the gun box in the boxes array
        void setBox();

        // the gun box index in the boxes array
        int boxesIndex;

};

#endif