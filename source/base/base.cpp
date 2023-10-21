#include "base.h"

base::base(vector2d *screenSize)
{
    this->screenSize = *screenSize;

    screenOffset = vector2d(0, 0);

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    this->window = SDL_CreateWindow("Caffeine World", 0, 0, screenSize->X, screenSize->Y, 0);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    this->mainRenderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

base::~base()
{
    if(window){
        SDL_DestroyWindow(window);
    }
    if(mainRenderer){
        SDL_DestroyRenderer(mainRenderer);
    }

}

int base::randomRange(int min, int max)
{
    return rand()%(max-min)+min;
}
