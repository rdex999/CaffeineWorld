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
        containerObj->handleEvent();
        containerObj->runTicks();

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
    playerObj = new player(baseObj);
}

container::~container()
{
    if(baseObj){delete baseObj;}
    if(backgroundObj){delete backgroundObj;}
    if(playerObj){delete playerObj;}

    SDL_Quit();
}

void container::handleEvent()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            // In case user requests exit, quit the game.
            case SDL_WINDOWEVENT_CLOSE: 
                std::cout << "Quiting." << std::endl;
                baseObj->run = false; 
                break;

            case SDL_QUIT:
                std::cout << "Quiting." << std::endl;
                baseObj->run = false; 
                break;

            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    // add in future
                    case SDLK_ESCAPE:
                        break;

                    default:
                        break;
                }
                break; 
            }

            default:
                break;
        }
    }
}

void container::runTicks()
{
    for(box* b: baseObj->boxes){
        if(b->shouldTick){
            b->tick();
        }
    }
}