#pragma once
#include <array>
#include "../base/base.h"
#include "../player/player.h"
#include "../bullet/bullet.h"

class gun
{
    public:
        gun(base* baseObj, player* playerObj);
        ~gun();

        // an array of bullet pointers
        bullet* bullets[16];

        // reload the gun
        void reload();

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

        // time since the last gun shot
        double lastGunShotTime;

        // a pointer to the gun box
        box* boxPtr;

        // the current bullet in the bullets array
        int currentBullet;
};