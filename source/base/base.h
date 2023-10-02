#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../vector2d/vector2d.h"

// basic variables and functions that almost every class will need
typedef struct base
{
    base(vector2d* screenSize);
    ~base();

    // game state
    bool run = true;

    // time between each frame
    double deltaTime = 0;

    double rotationPlayerToMouse;

    // renderer and window pointers
    SDL_Renderer* mainRenderer;
    SDL_Window* window;

    // the size of the screen
    vector2d screenSize;

    // the mouse location on the screen
    vector2d mouseLocation;

    // the mouse state 1 = left click, 2 = middle click, 3 = right click
    Uint32 mouseState;

    // returns a texture of the text with the given size, color, and font
    SDL_Texture* createTextTexture(const char* fontPath, const char* text, SDL_Color color, int fontSize, int* width, int* height);

    // returns a random number between min and max
    int randomRange(int min, int max);

} base;