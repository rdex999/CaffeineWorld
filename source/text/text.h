#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace text
{
    // returns a texture of the text with the given size, color, and font
    SDL_Texture* createTextTexture(SDL_Renderer* renderer, const char* fontPath, const char* text,
        SDL_Color color, int fontSize, int* width, int* height);

    // returns a texture of the text with an outline
    SDL_Texture* createTextOutlineTexture(SDL_Renderer* renderer, const char* fontPath, const char* text,
        SDL_Color color, SDL_Color outlineColor, int fontSize, int outlineSize, int* width, int* height);

}