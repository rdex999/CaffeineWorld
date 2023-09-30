#pragma once
#include <SDL2/SDL_image.h>
#include "../base/base.h"
#include "../dVector2d/dVector2d.h"

class bullet
{
    public:
        bullet(base* baseObj, vector2d *shootFrom, bool flip, bullet** bullets = nullptr, int bulletIndex = 0);
        ~bullet();

        // from where the bullet was shot,
        // and also the bullets location on the screen
        dVector2d shootFrom;
    
        // runs every frame
        void tick();
    
    private:

        // store pointers
        base* baseObj;

        // renders the bullet to the screen
        void render();

        // bullet texture
        SDL_Texture* texture;

        // the size of the bullet image 
        vector2d size;

        // the bullet rotation on the screen (radians)
        double rotation;

        // if the bullet texture should be fliped
        bool flip;

        // the bullet speed
        float speed;

        // this bullets index in the bullets array
        int bulletIndex;
        
        // the bullets array pointer. 
        bullet** bullets;
};