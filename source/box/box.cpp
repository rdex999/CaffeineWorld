#include "box.h"

box::box(std::function<void(double)> tick)
{
    this->tick = tick;
}