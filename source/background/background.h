#pragma once
#include <SDL2/SDL_image.h>
#include "../base/base.h"

class background
{
    public:
        background(base* baseObj);
        ~background();

    private:

        // renders the background, acts line the tick function because the background doesnt really need a tick function
        void render(double deltaTime);

        // the baseObj pointer
        base* baseObj;

        // the texture
        SDL_Texture* texture;
};