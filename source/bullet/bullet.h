#ifndef BULLET_H
#define BULLET_H
#include "../base/base.h"
#include "../player/player.h"

class bullet
{
    public:
        bullet(base* baseObj, player* playerObj);
        ~bullet();

    private:

        // store pointers
        base* baseObj;
        player* playerObj;

        // renders the bullet to the screen
        void render();

        // runs every frame
        void tick(double deltaTime);

        // bullet texture
        SDL_Texture* texture;

        // the location of the bullet on the screen
        vector2d screenLocation;
        
        // the size of the bullet image 
        vector2d size;

};

#endif