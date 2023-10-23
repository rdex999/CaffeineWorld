#pragma once
#include <array>
#include "../player/player.h"
#include "../bullet/bullet.h"
#include "../item/item.h"

class gun : public item
{
    public:
        gun(base* baseObj, player* playerObj);
        ~gun() override;

        // an array of bullet pointers
        bullet bullets[16];

        // reload the gun
        void reload();

        // runs every frame 
        void tick() override;
    
    private:

        // store object pointers
        base* baseObj;
        player* playerObj;

        // the texture of the gun
        SDL_Texture* texture;

        // the texture of the bullets
        SDL_Texture* textureBullet;

        // renders the gun
        void render();

        // the size of the gun image
        vector2d gunSize;

        // time since the last gun shot
        double lastGunShotTime;
};