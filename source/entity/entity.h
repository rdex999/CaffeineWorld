#pragma once
#include "../base/base.h"

enum entityId: unsigned char
{
    entityPlayer,
    entityZombie
};

class entity
{
    public:

        // runs every frame 
        virtual void tick() = 0;

        virtual ~entity();

        virtual void takeDemage(float demageAmount);

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

        // if the entity should jump
        bool jump;

        // jumping intensity
        float jumpIntensity;

        // the slow falling when starting to fall
        float gravitySlowDown;

        // the type of entity
        // (see the entityId enum below)
        entityId entityID;

        // the hp of the entity
        float life;

        // the max hp of the entity
        float maxLife;

    protected:

        // allways store base pointer
        base* baseObj;

        // renders the entity to the screen
        virtual void render() = 0;

};