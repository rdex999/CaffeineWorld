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

SDL_Texture *base::createTextTexture(const char *fontPath, const char *text, SDL_Color color, int fontSize, int* width, int* height)
{
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if(!font){
        std::cout << "Error: could not open font \"" << fontPath << "\".\n" << TTF_GetError() << std::endl;
        exit(1);
    }
 
    SDL_Surface* tempFontSurface = TTF_RenderText_Solid(font, text, color);
    if(!tempFontSurface){
        std::cout << "Error: could create font surface.\n" << TTF_GetError() << std::endl;
        exit(1);
    }

    *width = tempFontSurface->w;
    *height = tempFontSurface->h;
    TTF_CloseFont(font);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mainRenderer, tempFontSurface);
    if(!texture){
        std::cout << "Error: could not create text texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_FreeSurface(tempFontSurface);

    return texture;
}

SDL_Texture *base::createTextOutlineTexture(const char *fontPath, const char *text,
    SDL_Color color, SDL_Color outlineColor, int fontSize, int outlineSize, int *width, int *height)
{
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    TTF_Font* fontOutline = TTF_OpenFont(fontPath, fontSize);
    if(!font || !fontOutline){
        std::cout << "Error: could not open font \"" << fontPath << "\".\n" << TTF_GetError() << std::endl;
        exit(1);
    }

    TTF_SetFontOutline(fontOutline, outlineSize);

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);
    SDL_Surface* outlineSurface = TTF_RenderText_Blended(fontOutline, text, outlineColor);
    if(!textSurface || !outlineSurface){
        std::cout << "Error: could not create text/outline surface.\n" << TTF_GetError() << std::endl;
        exit(1);
    }

    *width = textSurface->w;
    *height = textSurface->h;

    SDL_Rect rect = {outlineSize, outlineSize, textSurface->w, textSurface->h};

    SDL_SetSurfaceBlendMode(textSurface, SDL_BLENDMODE_BLEND);
    SDL_BlitSurface(textSurface, NULL, outlineSurface, &rect);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(mainRenderer, outlineSurface);
    if(!texture){
        std::cout << "Error: could not create text outline texture.\n" << SDL_GetError() << std::endl;
        exit(1);
    }

    TTF_CloseFont(font);
    TTF_CloseFont(fontOutline);
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(outlineSurface);

    return texture;

}

int base::randomRange(int min, int max)
{
    return rand()%(max-min)+min;
}
