#include "box.h"

box::box(SDL_Texture *texture, vector2d *startPosition,
    vector2d *endPosition, bool shouldTick, std::function<void(double)> tick, bool flip)
{
    this->texture = texture;
    this->startPosition = *startPosition;
    this->endPosition= *endPosition;
    this->shouldTick = shouldTick;
    this->tick = tick;
    this->flip = flip;
}

box::box(SDL_Texture *texture, vector2d startPosition,
    vector2d endPosition, bool shouldTick, std::function<void(double)> tick, bool flip)
{
    this->texture = texture;
    this->startPosition = startPosition;
    this->endPosition= endPosition;
    this->shouldTick = shouldTick;
    this->tick = tick;
    this->flip = flip;
}