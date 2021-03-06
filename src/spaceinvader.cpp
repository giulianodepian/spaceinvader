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
    state = start;
    rightKeyPressed = false;
    leftKeyPressed = false;
    zWasPressed = false;
    returnKeyPressed = false;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    collisionObserver = new CollisionObserver();
    player = new Player(SCREEN_WIDTH, SCREEN_HEIGHT);
    playerSurface = IMG_Load("./media/sprites/player.png");
    playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
    SDL_FreeSurface(playerSurface);
    playerDeathSurface = IMG_Load("./media/sprites/playerDeath.png");
    PlayerDeathTexture = SDL_CreateTextureFromSurface(renderer, playerDeathSurface);
    SDL_FreeSurface(playerDeathSurface);
    bulletSurface = IMG_Load("./media/sprites/bullet.png");
    bulletTexture = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    SDL_FreeSurface(bulletSurface);
    for (int i = 0; i < 11; i++ ) {
        for (int k = 0; k < 5; k++) {
            if (k == 0) enemies[i][k] = new Enemy(i, k, small, SCREEN_WIDTH, SCREEN_HEIGHT);
            else if (k > 0 && k < 3) enemies[i][k] = new Enemy(i, k, medium, SCREEN_WIDTH, SCREEN_HEIGHT);
            else enemies[i][k] = new Enemy(i, k, large, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    };
    enemySmall1Surface = IMG_Load("./media/sprites/small1.png");
    enemySmall2Surface = IMG_Load("./media/sprites/small2.png");
    enemyMedium1Surface = IMG_Load("./media/sprites/medium1.png");
    enemyMedium2Surface = IMG_Load("./media/sprites/medium2.png");
    enemyLarge1Surface = IMG_Load("./media/sprites/large1.png");
    enemyLarge2Surface = IMG_Load("./media/sprites/large2.png");
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
    deathEnemySurface = IMG_Load("./media/sprites/enemyDeath.png");
    deathEnemyTexture = SDL_CreateTextureFromSurface(renderer, deathEnemySurface);
    SDL_FreeSurface(deathEnemySurface);
    enemyLaserSurface = IMG_Load("./media/sprites/enemyLaser.png");
    enemyLaserTexture = SDL_CreateTextureFromSurface(renderer, enemyLaserSurface);
    SDL_FreeSurface(enemyLaserSurface);

    TTF_Init();
    font = TTF_OpenFont("./media/fonts/EightBit Atari-Proport6.ttf", 8);
    scorePos.x = 0;
    scorePos.y = 0;
    scorePos.h = 30;
    scorePos.w = 300;
    livesPos.x = SCREEN_WIDTH - 200;
    livesPos.y = 0;
    livesPos.w = 200;
    livesPos.h = 30;
    SDL_Color textColor = {255,255,255};
    gameOverTextSurface = TTF_RenderText_Solid(font, "GAME OVER", textColor);
    gameOverTextTexture = SDL_CreateTextureFromSurface(renderer, gameOverTextSurface);
    SDL_FreeSurface(gameOverTextSurface);
    startTextSurface = TTF_RenderText_Solid(font, "PRESS START TO PLAY", textColor);
    startTextTexture = SDL_CreateTextureFromSurface(renderer, startTextSurface);
    SDL_FreeSurface(startTextSurface);
    timer = SDL_AddTimer(1000, timerCallback, NULL);
    detectecCollision = false;
    exitProgram = false;
}

SpaceInvader::~SpaceInvader() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(enemySmall1Texture);
    SDL_DestroyTexture(enemySmall2Texture);
    SDL_DestroyTexture(enemyMedium1Texture);
    SDL_DestroyTexture(enemyMedium2Texture);
    SDL_DestroyTexture(enemyLarge1Texture);
    SDL_DestroyTexture(enemyLarge2Texture);
    SDL_DestroyTexture(deathEnemyTexture);
    SDL_DestroyTexture(enemyLaserTexture);
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
                    if (player->getState() != destroyed && state != start) leftKeyPressed = true;
                    break;
                
                case SDL_SCANCODE_RIGHT:
                    if (player->getState() != destroyed && state != start)rightKeyPressed = true;
                    break;

                case SDL_SCANCODE_Z:
                    if (player->getState() == normal && state != start) {
                        zWasPressed = true;
                    }
                    break;
                
                case SDL_SCANCODE_RETURN:
                    if (state == start) returnKeyPressed = true;
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
                    if (state != ending && state != start) {
                        for (int i = 0; i < 11; i++) {
                            if (enemies[i][0]->detectCollision()) {
                                detectecCollision = true;
                                for (int j = 0; j < 11; j++) {
                                    for (int l = 0; l < 5; l++) {
                                        if (enemies[j][l]->getState() != destroyed) {
                                            enemies[j][l]->verticalMovement();
                                        }
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
                                    if (enemies[i][k]->getState() != destroyed) {
                                        enemies[i][k]->horizontalMovement();
                                    }
                                }
                            }
                        }
                        break;
                    }
                default:
                    break;
                }
        default:
            break;
        }
    }
}

void SpaceInvader::update() {
    if (leftKeyPressed && player->getState() != destroyed && state != start) {
        player->movement(-1);
    }
    if(rightKeyPressed && player->getState() != destroyed && state != start) {
        player->movement(1);
    }

    if(player->getState() == shooting) {
        player->bulletMovement();
    }

    if(zWasPressed && player->getState() != destroyed && state != start) {
        player->setState(shooting);
        zWasPressed = false;
    }

    if (returnKeyPressed && state == start) {
        state = playing;
        returnKeyPressed = false;
    }

    if (player->getKillCount() == 55 && state == ending) {
        for (int i = 0; i < 11; i++) {
            for (int k = 0; k < 5; k++) {
                enemies[i][k]->resetPosition();
                enemies[i][k]->setState(normal);
                enemies[i][k]->setPlayDeathAnimation(true);
            }
        }
        state = playing;
        player->setKillCount(0);
        SDL_Delay(2000);
    }

    

    if (player->getKillCount() == 55) state = ending;

    if (player->getState() == destroyed) {
        for (int i = 0; i < 11; i++) {
            for (int k = 0; k < 5; k++) {
                enemies[i][k]->resetPosition();
                if (enemies[i][k]->getState() == shooting) enemies[i][k]->setState(normal);
                if (player->getLives() == 0) { 
                    enemies[i][k]->setState(normal);
                    enemies[i][k]->setPlayDeathAnimation(true);
                }
            }
        }
        if (player->getLives() > 0) {
            player->setState(normal);
            state = playing;
            SDL_Delay(1500);
        } else {
            player->setState(normal);
            state = start;
            player->setLives(3);
            player->setScore(0);
            SDL_Delay(1500);
        }
    }

    if  (state != start) {
        for (int i = 0; i < 11; i++) {
            for (int j = 4; j >= 0; j--) {
                bool loopBreak = false;
                if (enemies[i][j]->getState() == shooting) {
                    enemies[i][j]->bulletMovement();
                    loopBreak = true;
                }

                if (player->getState() != destroyed && !loopBreak) {
                    if (enemies[i][j]->getState() == normal) {
                        loopBreak = true;
                        if ((rand() % 400 + 1) == 1) {
                            enemies[i][j]->setState(shooting);
                        }
                    }
                }
                if (loopBreak) break;
            }
        }
        collisionObserver->update(player, enemies);
    }

}

void SpaceInvader::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_Color textColor = {255,255,255};
    std::string scoreText = "SCORE: ";
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText.append(std::to_string(player->getScore())).c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &scorePos);
    SDL_DestroyTexture(textTexture);
    std::string livesText = "LIVES: ";
    SDL_Surface *livesTextSurface = TTF_RenderText_Solid(font, livesText.append(std::to_string(player->getLives())).c_str(), textColor);
    SDL_Texture *livesTextTexture = SDL_CreateTextureFromSurface(renderer, livesTextSurface);
    SDL_FreeSurface(livesTextSurface);
    SDL_RenderCopy(renderer, livesTextTexture, NULL, &livesPos);
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
                if (enemies[i][k]->getState() == shooting) {
                    SDL_Rect enemyBulletPos;
                    enemyBulletPos.x = enemies[i][k]->getBulletX();
                    enemyBulletPos.y = enemies[i][k]->getBulletY();
                    enemyBulletPos.w = enemies[i][k]->getBulletW();
                    enemyBulletPos.h = enemies[i][k]->getBulletH();
                    SDL_RenderCopy(renderer, enemyLaserTexture, NULL, &enemyBulletPos);
                }
            } else if (enemies[i][k]->getPlayDeathAnimation()){
                SDL_Rect enemyPos;
                enemyPos.x = enemies[i][k]->getX();
                enemyPos.y = enemies[i][k]->getY();
                enemyPos.h = Enemy::HEIGHT;
                enemyPos.w = enemies[i][k]->getW();
                SDL_RenderCopy(renderer, deathEnemyTexture, NULL, &enemyPos);
            }
        }
    }
    if (player->getState() != destroyed) SDL_RenderCopy(renderer, playerTexture, NULL, &playerPos);
    else SDL_RenderCopy(renderer, PlayerDeathTexture, NULL, &playerPos);
    if (player->getLives() == 0) {
        SDL_Rect gameOverPos;
        gameOverPos.x = SCREEN_WIDTH / 2 - (200 / 2);
        gameOverPos.y = SCREEN_HEIGHT / 2;
        gameOverPos.h = 30;
        gameOverPos.w = 200;
        SDL_RenderCopy(renderer, gameOverTextTexture, NULL, &gameOverPos);
    }
    if (state == start) {
        SDL_Rect startPos;
        startPos.x = SCREEN_WIDTH / 2 - (200 / 2);
        startPos.y = SCREEN_HEIGHT / 2;
        startPos.h = 30;
        startPos.w = 200;
        SDL_RenderCopy(renderer, startTextTexture, NULL, &startPos);
    }
    SDL_RenderPresent(renderer);
}