#include "spaceinvader.h"

SpaceInvader::SpaceInvader(){
    rightKeyPressed = false;
    leftKeyPressed = false;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    player = new Player(SCREEN_WIDTH, SCREEN_HEIGHT);
    playerSurface = IMG_Load("./media/player.png");
    if (!playerSurface) {
        std::cout << IMG_GetError;
    }
    playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
    exitProgram = false;
}

SpaceInvader::~SpaceInvader() {
    SDL_FreeSurface(playerSurface);
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
}

void SpaceInvader::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_Rect playerPos;
    playerPos.x = player->getX();
    playerPos.y = SCREEN_HEIGHT - player->getH();
    playerPos.h = player->getH();
    playerPos.w = player->getW();
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerPos);
    SDL_RenderPresent(renderer);
}