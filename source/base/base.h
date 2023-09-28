#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "../vector2d/vector2d.h"
#include "../box/box.h"

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

    vector2d screenSize;

    // the mouse location on the screen
    vector2d mouseLocation;

    // the mouse state 1 = left click, 2 = middle click, 3 = right click
    Uint32 mouseState;

    // the boxes vector. each box containes detailes on how it should be rendered
    std::vector<box*> boxes;
} base;

#endif