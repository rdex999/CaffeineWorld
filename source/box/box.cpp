#include "box.h"

box::box(SDL_Texture *texture, vector2d *startPosition, vector2d *endPosition)
{
    this->texture = texture;
    this->startPosition = *startPosition;
    this->endPosition= *endPosition;
}

box::box(SDL_Texture *texture, vector2d startPosition, vector2d endPosition)
{
    this->texture = texture;
    this->startPosition = startPosition;
    this->endPosition= endPosition;
}