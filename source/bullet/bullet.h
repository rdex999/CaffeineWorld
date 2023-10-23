#pragma once
#include <SDL2/SDL_image.h>
#include "../base/base.h"
#include "../dVector2d/dVector2d.h"
#include "../entity/entity.h"

class bullet
{
    public:
        bullet(base* baseObj, vector2d *shootFrom, bool flip, SDL_Texture* texture);
        bullet() = default;
        ~bullet();

        // if the bullet is active
        bool isActive = false;

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

        // the bullet rotation on the screen (radians)
        double rotation;

        // if the bullet texture should be fliped
        bool flip;

        // the bullet speed
        float speed;
};