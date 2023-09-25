#ifndef BOX_H
#define BOX_H
#include <functional>

// A container for a tick function and a render function for each object.
// The renderer then loops throgh an array (vector) of boxes and renderer each texture of the position.
typedef struct box
{
    box(std::function<void()> render, std::function<void(double)> tick = nullptr);

    std::function<void(double)> tick;
    std::function<void()> render;

} box;

#endif