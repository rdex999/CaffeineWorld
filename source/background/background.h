#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SDL2/SDL_image.h>
#include "../base/base.h"

class background
{
    public:
        background(base* baseObj);
        ~background();

    private:

        // renders the background
        void render();

        // the baseObj pointer
        base* baseObj;

        // the texture
        SDL_Texture* texture;
};

#endif