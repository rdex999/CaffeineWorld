#include "base.h"

base::base(vector2d *screenSize)
{
    this->screenSize = *screenSize;
    
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

SDL_Texture *base::createTextTexture(const char *fontPath, const char *text, SDL_Color color, int fontSize, int* width, int* height)
{
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if(!font){
        std::cout << "Error: could not open font \"" << fontPath << "\".\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_Surface* tempFontSurface = TTF_RenderText_Solid(font, text, color);
    if(!tempFontSurface){
        std::cout << "Error: could create font surface.\n" << SDL_GetError() << std::endl;
        exit(1);
    }
    *width = tempFontSurface->w;
    *height = tempFontSurface->h;
    TTF_CloseFont(font);
    return SDL_CreateTextureFromSurface(mainRenderer, tempFontSurface);
}

int base::randomRange(int min, int max)
{
    return rand()%(max-min)+min;
}
