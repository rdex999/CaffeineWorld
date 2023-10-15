#pragma once
#include "../base/base.h"

class entity
{
    public:

        // runs every frame 
        virtual void tick() = 0;

        virtual ~entity();

        // the location of the entity on the screen
        vector2d location;

        // if the entity is in the air
        bool inAir;

        // if the entity texture should flip
        bool flip;

        // if the entity is blocked by a wall from the right
        bool blockedRight;

        // if the entity is blocked by a wall from the left
        bool blockedLeft;

    protected:

        // allways store base pointer
        base* baseObj;

        // renders the entity to the screen
        virtual void render() = 0;

};