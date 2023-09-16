#ifndef MAIN_H
#define MAIN_H
#include "base/base.h"
#include "background/background.h"
#include "player/player.h"

// container for all of the components
typedef struct container
{
    container();
    ~container();

    base* baseObj;
    background* backgroundObj;
    player* playerObj;

    // handle keyboard
    void handleEvent();

    // runs all the tick functions from the boxes array 
    void runTicks();
} container;

#endif