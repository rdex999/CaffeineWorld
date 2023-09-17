#include "main.h"

int main()
{
    srand(time(NULL));
    container* containerObj = new container;

    Uint64 deltaTimeNow = SDL_GetPerformanceCounter();
    Uint64 deltaTimeLast = 0;
    while(containerObj->baseObj->run)
    {
        deltaTimeLast = deltaTimeNow;
        deltaTimeNow = SDL_GetPerformanceCounter();
        containerObj->baseObj->deltaTime = ((deltaTimeNow - deltaTimeLast)*1000 / (double)SDL_GetPerformanceFrequency())*0.001;

        containerObj->baseObj->renderBoxes();
        containerObj->handleEvent();
        containerObj->runTicks();
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
    inventoryObj = new inventory(baseObj, playerObj);
}

container::~container()
{
    if(baseObj){delete baseObj;}
    if(backgroundObj){delete backgroundObj;}
    if(playerObj){delete playerObj;}
    if(inventoryObj){delete inventoryObj;}

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

                    case SDLK_SPACE:
                    case SDLK_w:
                    case SDLK_UP:
                        playerObj->doJump(); 
                        break;

                    default:
                        break;
                }
                break; 
            }

            case SDL_KEYUP:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_d:
                    case SDLK_RIGHT:
                        playerObj->walkingSlowDown = 0; 
                        playerObj->stoppedWalking = -1;
                        break;

                    case SDLK_a:
                    case SDLK_LEFT:
                        playerObj->walkingSlowDown = 0; 
                        playerObj->stoppedWalking = 1;
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
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]){
        playerObj->walk(-1);
    }
    if(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]){
        playerObj->walk(1);
    }
}

void container::runTicks()
{
    for(box* b: baseObj->boxes){
        if(b->shouldTick){
            b->tick(baseObj->deltaTime);
        }
    }
}