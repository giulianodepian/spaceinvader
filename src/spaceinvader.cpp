#include "spaceinvader.h"

Uint32 timerCallback(Uint32 interval, void *param) {
    SDL_Event event;
    SDL_UserEvent userevent;
    userevent.type = SDL_USEREVENT;
    userevent.code = 2;
    userevent.data1 = NULL;
    userevent.data2 = NULL;
    event.type = SDL_USEREVENT;
    event.user = userevent;
    SDL_PushEvent(&event);
    return(interval);
}

SpaceInvader::SpaceInvader(){
    rightKeyPressed = false;
    leftKeyPressed = false;
    zWasPressed = false;
    score = 0;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    player = new Player(SCREEN_WIDTH, SCREEN_HEIGHT);
    playerSurface = IMG_Load("./media/player.png");
    playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
    SDL_FreeSurface(playerSurface);
    bulletSurface = IMG_Load("./media/bullet.png");
    bulletTexture = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    SDL_FreeSurface(bulletSurface);
    for (int i = 0; i < 11; i++ ) {
        for (int k = 0; k < 5; k++) {
            if (k == 0) enemies[i][k] = new Enemy(i, k, small, SCREEN_WIDTH, SCREEN_HEIGHT);
            else if (k > 0 && k < 3) enemies[i][k] = new Enemy(i, k, medium, SCREEN_WIDTH, SCREEN_HEIGHT);
            else enemies[i][k] = new Enemy(i, k, large, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    };
    enemySmall1Surface = IMG_Load("./media/small1.png");
    enemySmall2Surface = IMG_Load("./media/small2.png");
    enemyMedium1Surface = IMG_Load("./media/medium1.png");
    enemyMedium2Surface = IMG_Load("./media/medium2.png");
    enemyLarge1Surface = IMG_Load("./media/large1.png");
    enemyLarge2Surface = IMG_Load("./media/large2.png");
    enemySmall1Texture = SDL_CreateTextureFromSurface(renderer, enemySmall1Surface);
    enemySmall2Texture = SDL_CreateTextureFromSurface(renderer, enemySmall2Surface);
    enemyMedium1Texture = SDL_CreateTextureFromSurface(renderer, enemyMedium1Surface);
    enemyMedium2Texture = SDL_CreateTextureFromSurface(renderer, enemyMedium2Surface);
    enemyLarge1Texture = SDL_CreateTextureFromSurface(renderer, enemyLarge1Surface);
    enemyLarge2Texture = SDL_CreateTextureFromSurface(renderer, enemyLarge2Surface);
    SDL_FreeSurface(enemySmall1Surface);
    SDL_FreeSurface(enemySmall2Surface);
    SDL_FreeSurface(enemyMedium1Surface);
    SDL_FreeSurface(enemyMedium2Surface);
    SDL_FreeSurface(enemyLarge1Surface);
    SDL_FreeSurface(enemyLarge2Surface);
    timer = SDL_AddTimer(1000, timerCallback, NULL);
    detectecCollision = false;
    exitProgram = false;
}

SpaceInvader::~SpaceInvader() {
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(enemySmall1Texture);
    SDL_DestroyTexture(enemySmall2Texture);
    SDL_DestroyTexture(enemyMedium1Texture);
    SDL_DestroyTexture(enemyMedium2Texture);
    SDL_DestroyTexture(enemyLarge1Texture);
    SDL_DestroyTexture(enemyLarge2Texture);
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
        case SDL_USEREVENT:
            switch(event.user.code) {
                case 2:
                    for (int i = 0; i < 11; i++) {
                        if (enemies[i][0]->detectCollision()) {
                            detectecCollision = true;
                            for (int j = 0; j < 11; j++) {
                                for (int l = 0; l < 5; l++) {
                                    enemies[j][l]->verticalMovement();
                                }
                            }
                            break;
                        } else {
                            detectecCollision = false;
                        }
                    }
                    if (!detectecCollision) {
                        for (int i = 0; i < 11; i++) {
                            for (int k = 0; k < 5; k++) {
                                enemies[i][k]->horizontalMovement();
                            }
                        }
                    }
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

    if (player->getState() == shooting) {
        bool breakLoop = false;
        for (int i = 0; i < enemies.size(); i++) {
            for (int k = 0; k < enemies[i].size(); k++) {
                if (enemies[i][k]->getState() != destroyed) {
                    if (
                        player->getBulletY() <= enemies[i][k]->getY() + Enemy::HEIGHT && (
                            (player->getBulletX() >= enemies[i][k]->getX() && player->getBulletX() <= enemies[i][k]->getX() + enemies[i][k]->getW()) ||
                            (player->getBulletX() + player->getBulletW() >= enemies[i][k]->getX() && player->getBulletX() + player->getBulletW() <= enemies[i][k]->getX() + enemies[i][k]->getW())
                        )
                    ) {
                        enemies[i][k]->setState(destroyed);
                        player->setState(normal);
                        player->resetBullet();
                        breakLoop = true;
                        break;
                    }
                }
            }
            if (breakLoop) break;
        }
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
    for (int i = 0; i < 11; i++) {
        for (int k = 0; k < 5; k++) {
            if (enemies[i][k]->getState() != destroyed) {
                SDL_Rect enemyPos;
                enemyPos.x = enemies[i][k]->getX();
                enemyPos.y = enemies[i][k]->getY();
                enemyPos.h = Enemy::HEIGHT;
                enemyPos.w = enemies[i][k]->getW();
                switch(enemies[i][k]->getType()) {
                    case small:
                        if (enemies[i][k]->getCurrentAnim() == 1) SDL_RenderCopy(renderer, enemySmall1Texture, NULL, &enemyPos);
                        else SDL_RenderCopy(renderer, enemySmall2Texture, NULL, &enemyPos);
                        break;
                    case medium:
                        if (enemies[i][k]->getCurrentAnim() == 1) SDL_RenderCopy(renderer, enemyMedium1Texture, NULL, &enemyPos);
                        else SDL_RenderCopy(renderer, enemyMedium2Texture, NULL, &enemyPos);
                        break;
                    case large:
                        if (enemies[i][k]->getCurrentAnim() == 1) SDL_RenderCopy(renderer, enemyLarge1Texture, NULL, &enemyPos);
                        else SDL_RenderCopy(renderer, enemyLarge2Texture, NULL, &enemyPos);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerPos);
    SDL_RenderPresent(renderer);
}