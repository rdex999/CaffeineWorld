#include "main.h"

int main()
{
    srand(time(NULL));
    container containerObj;

    Uint64 deltaTimeNow = SDL_GetPerformanceCounter();
    Uint64 deltaTimeLast = 0;
    while(containerObj.baseObj->run)
    {
        deltaTimeLast = deltaTimeNow;
        deltaTimeNow = SDL_GetPerformanceCounter();
        containerObj.baseObj->deltaTime = ((deltaTimeNow - deltaTimeLast)*1000 / (double)SDL_GetPerformanceFrequency())*0.001;

        containerObj.handleEvent();
        containerObj.runTicks();
    }

    return 0;
}

container::container()
{
    vector2d screenSize(1920, 1080);

    baseObj = new base(&screenSize);
    backgroundObj = new background(baseObj);
    playerObj = new player(baseObj);
    itemsHeadObj = new itemsHead(baseObj, playerObj);
    entitysHeadObj = new entitysHead(baseObj, playerObj);
    blocksHeadObj = new blocksHead(baseObj, playerObj);
    inventoryObj = new inventory(baseObj, playerObj, itemsHeadObj);
}

container::~container()
{
    if(backgroundObj){delete backgroundObj;}
    if(playerObj){delete playerObj;}
    if(itemsHeadObj){delete itemsHeadObj;}
    if(entitysHeadObj){delete entitysHeadObj;}
    if(blocksHeadObj){delete blocksHeadObj;}
    if(inventoryObj){delete inventoryObj;}

    if(baseObj){delete baseObj;}
    SDL_Quit();
}

void container::handleEvent()
{
    int x, y;
    baseObj->mouseState = SDL_GetMouseState(&x, &y);
    baseObj->mouseLocation.X = x;
    baseObj->mouseLocation.Y = y;
 
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

            case SDL_MOUSEWHEEL:

                // if the player scolls their mouse 
                if(event.wheel.y != 0){
                    inventoryObj->selectItemOffset(event.wheel.y*-1);
                }
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

                    case SDLK_r:
                        itemsHeadObj->gunObj->reload();
                        break;

                    case SDLK_0:
                        inventoryObj->selectItem(10);
                        break;

                    case SDLK_1:
                        inventoryObj->selectItem(1);
                        break;

                    case SDLK_2:
                        inventoryObj->selectItem(2);
                        break;

                    case SDLK_3:
                        inventoryObj->selectItem(3);
                        break;

                    case SDLK_4:
                        inventoryObj->selectItem(4);
                        break;

                    case SDLK_5:
                        inventoryObj->selectItem(5);
                        break;
 
                    case SDLK_6:
                        inventoryObj->selectItem(6);
                        break;

                    case SDLK_7:
                        inventoryObj->selectItem(7);
                        break;

                    case SDLK_8:
                        inventoryObj->selectItem(8);
                        break;

                    case SDLK_9:
                        inventoryObj->selectItem(9);
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
                        playerObj->setTextureStand();
                        break;

                    case SDLK_a:
                    case SDLK_LEFT:
                        playerObj->walkingSlowDown = 0;
                        playerObj->stoppedWalking = 1;
                        playerObj->setTextureStand();
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
    backgroundObj->tick();
    playerObj->tick();
    itemsHeadObj->tick();
    entitysHeadObj->tick();
    blocksHeadObj->tick();
    inventoryObj->tick();
    SDL_RenderPresent(baseObj->mainRenderer);

    baseObj->screenOffset = vector2d(0, 0);
}