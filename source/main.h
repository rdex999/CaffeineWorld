#ifndef MAIN_H
#define MAIN_H
#include "base/base.h"
#include "background/background.h"

// container for all of the components
typedef struct container
{
    container();
    ~container();

    base* baseObj;
    background* backgroundObj;

    // handle keyboard
    void handleEvent();
} container;

#endif