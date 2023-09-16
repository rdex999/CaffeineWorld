#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
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

    // renderer and window pointers
    SDL_Renderer* mainRenderer;
    SDL_Window* window;

    vector2d screenSize;

    // the boxes vector. each box containes detailes on how it should be rendered
    std::vector<box*> boxes;

    // renders each texture from each box in the boxes array 
    void renderBoxes();
} base;

#endif