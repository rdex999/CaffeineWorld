#ifndef BOX_H
#define BOX_H
#include <functional>

// A container for a tick function, the container the loops through an vector of boxes and runs their tick function.
typedef struct box
{
    box(std::function<void(double)> tick);

    std::function<void(double)> tick;
} box;

#endif