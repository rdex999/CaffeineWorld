#ifndef BOX_H
#define BOX_H
#include <functional>
#include "../vector2d/vector2d.h"

// A container for a texture and a start position and a end position.
// The renderer then loops throgh an array (vector) of boxes and renderer each texture of the position.
// Note 1: THIS DOES NOT DESTROY THE TEXTURE
// Note 2: SOULD ONLY BE CREATED WITH THE 'new' KEYWORD
typedef struct box
{
    box(class SDL_Texture* texture, vector2d* startPosition,
        vector2d* endPosition, bool shouldTick = false, std::function<void(double)> tick = nullptr, bool flip = false);
    
    box(class SDL_Texture* texture, vector2d startPosition,
        vector2d endPosition, bool shouldTick = false, std::function<void(double)> tick = nullptr, bool flip = false);

    vector2d startPosition;
    vector2d endPosition;

    class SDL_Texture* texture;

    // if the tick function should be called or not
    bool shouldTick;

    // if the renderer should flip the texture, false for the default texture
    bool flip;

    std::function<void(double)> tick;
} box;

#endif