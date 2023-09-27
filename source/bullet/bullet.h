#ifndef BULLET_H
#define BULLET_H
#include <SDL2/SDL_image.h>
#include "../base/base.h"

class bullet
{
    public:
        bullet(base* baseObj, std::vector<box*>::iterator boxesIterator,
            vector2d &shootFrom, vector2d &shootTo, bool flip);
        ~bullet();

        // from where the bullet was shot,
        // and also the bullets location on the screen
        vector2d shootFrom;
    
    private:

        // store pointers
        base* baseObj;

        // renders the bullet to the screen
        void render();

        // runs every frame
        void tick(double deltaTime);

        // bullet texture
        SDL_Texture* texture;

        // the size of the bullet image 
        vector2d size;

        // where the bullet should go
        vector2d shootTo;

        // the bullet box iterator at the boxes array
        std::vector<box*>::iterator boxesIterator;

        // the bullet box pointer
        box* boxPtr;

        // the bullet rotation on the screen
        double rotation;

        // if the bullet texture should be fliped
        bool flip;
};

#endif