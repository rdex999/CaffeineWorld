#include "entity.h"

entity::~entity()
{
}

void entity::takeDemage(float demageAmount)
{
    life -= demageAmount;
}
