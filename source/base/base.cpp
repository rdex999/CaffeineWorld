#include "base.h"

base::base(vector2d *screenSize)
{
    this->screenSize = *screenSize;
    
    SDL_Init(SDL_INIT_VIDEO);
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

    for(box* b: boxes){
        if(b){
            delete b;
        }
    }
}

void base::renderBoxes()
{
    for(box* b: boxes){
        if(b && b->render){
            b->render();
        }
    }
    SDL_RenderPresent(mainRenderer);
}