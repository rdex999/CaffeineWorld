#include "box.h"

box::box(std::function<void()> render, std::function<void(double)> tick)
{
    this->render = render;
    this->tick = tick;
}