#pragma once
#include "../base/base.h"

class entity
{
    public:
        
        virtual void tick() = 0;

        vector2d location;

        // if the entity is in the air
        bool inAir;

        // if the entity texture should flip
        bool flip;

    protected:

        // allways store base pointer
        base* baseObj;

        virtual void render() = 0;

};