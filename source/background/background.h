#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SDL2/SDL_image.h>
#include "../base/base.h"

class background
{
    public:
        background(base* baseObj);
        ~background();

        SDL_Texture* texture;
};

#endif