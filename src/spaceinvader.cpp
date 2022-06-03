#include "spaceinvader.h"

SpaceInvader::SpaceInvader(){
    rightKeyPressed = false;
    leftKeyPressed = false;
    zWasPressed = false;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    player = new Player(SCREEN_WIDTH, SCREEN_HEIGHT);
    playerSurface = IMG_Load("./media/player.png");
    playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
    bulletSurface = IMG_Load("./media/bullet.png");
    bulletTexture = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    exitProgram = false;
}

SpaceInvader::~SpaceInvader() {
    SDL_FreeSurface(playerSurface);
    SDL_DestroyTexture(playerTexture);
    SDL_FreeSurface(bulletSurface);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SpaceInvader::execute() {
    while(!exitProgram) {
        input();
        update();
        render();
    }
}

void SpaceInvader::input() {
    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    exitProgram = true;
                    break;
                
                case SDL_SCANCODE_LEFT:
                    leftKeyPressed = true;
                    break;
                
                case SDL_SCANCODE_RIGHT:
                    rightKeyPressed = true;
                    break;

                case SDL_SCANCODE_Z:
                    if (player->getState() == normal) {
                        zWasPressed = true;
                    }
                    break;
                
                default:
                    break;
            }
            break;
        
        case SDL_KEYUP:
            switch(event.key.keysym.scancode)
            {
                case SDL_SCANCODE_LEFT:
                    leftKeyPressed = false;
                    break;
                case SDL_SCANCODE_RIGHT:
                    rightKeyPressed = false;
                    break;
                
                default:
                    break;
            }
        
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
                case SDL_WINDOWEVENT_CLOSE:
                    exitProgram = true;
                    break;
                default:
                    break;
            }
        default:
            break;
        }
    }
}

void SpaceInvader::update() {
    if (leftKeyPressed) {
        player->movement(-1);
    }
    if(rightKeyPressed) {
        player->movement(1);
    }

    if(player->getState() == shooting) {
        player->bulletMovement();
    }

    if(zWasPressed) {
        player->setState(shooting);
        zWasPressed = false;
    }
}

void SpaceInvader::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_Rect playerPos;
    playerPos.x = player->getX();
    playerPos.y = SCREEN_HEIGHT - player->getH();
    playerPos.h = player->getH();
    playerPos.w = player->getW();
    if (player->getState() == shooting) {
        SDL_Rect bulletPos;
        bulletPos.x = player->getBulletX();
        bulletPos.y = player->getBulletY();
        bulletPos.h = player->getBulletH();
        bulletPos.w = player->getBulletW();
        SDL_RenderCopy(renderer, bulletTexture, NULL, &bulletPos);
    }
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerPos);
    SDL_RenderPresent(renderer);
}