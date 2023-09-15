#include "main.h"

int main()
{
    srand(time(NULL));
    container* containerObj = new container;

    double deltaTimeStart = 0; 
    while(containerObj->baseObj->run)
    {
        deltaTimeStart = (double)time(NULL);

        containerObj->baseObj->renderBoxes();

        containerObj->baseObj->deltaTime = (double)(time(NULL) - deltaTimeStart);
    }

    delete containerObj; 
    return 0;
}

container::container()
{
    vector2d screenSize(1920, 1080);
    baseObj = new base(&screenSize);
    backgroundObj = new background(baseObj);
}

container::~container()
{
    if(baseObj){delete baseObj;}
    if(backgroundObj){delete backgroundObj;}
}