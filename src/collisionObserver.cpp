#include "collisionObserver.h"

Uint32 enemyDeathCallback(Uint32 interval, void *param) {
    Enemy *enemy = (Enemy *)param;
    enemy->setPlayDeathAnimation(false);
    return 0;
}

void CollisionObserver::update(Player *player, std::array<std::array<Enemy *, 5>, 11> enemies) {
    if (player->getState() == shooting) {
        bool breakLoop = false;
            for (int i = 0; i < 11; i++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (enemies[i][k]->getState() != destroyed)
                    {
                        if (
                            player->getBulletY() <= enemies[i][k]->getY() + Enemy::HEIGHT && (
                                (player->getBulletX() >= enemies[i][k]->getX() && player->getBulletX() <= enemies[i][k]->getX() + enemies[i][k]->getW()) ||
                                (player->getBulletX() + player->getBulletW() >= enemies[i][k]->getX() && player->getBulletX() + player->getBulletW() <= enemies[i][k]->getX() + enemies[i][k]->getW())
                            )
                        ) {
                            player->playerDestroyEnemy(enemies[i][k]->getScore());
                            enemies[i][k]->setState(destroyed);
                            breakLoop = true;
                            SDL_AddTimer(500, enemyDeathCallback, enemies[i][k]);
                            break;
                        }
                    }
                }
                if (breakLoop)
                    break;
            }
        }
        if (player->getState() != destroyed){
            for (int i = 0; i < 11; i++) {
                for (int k = 0; k < 5; k++) {
                    if ((player->getScreenH() - player->getH()) <= (enemies[i][k]->getY() + Enemy::HEIGHT)) {
                        player->enemyDestroyPlayer();
                        break;
                    }
                }
                if (player->getState() == destroyed) break;
            }
        }
        for (int i = 0; i < 11; i++) {
            for (int j = 4; j >= 0; j--) {
                if (player->getState() != destroyed) {
                    if (enemies[i][j]->getState() == shooting) {
                        if (
                            (
                                enemies[i][j]->getBulletX() <= player->getX() + player->getW() && enemies[i][j]->getBulletX() + enemies[i][j]->getBulletW() >= player->getX() 
                            ) 
                            &&
                            (
                                enemies[i][j]->getBulletY() <= player->getScreenH() && enemies[i][j]->getBulletY() + enemies[i][j]->getBulletH() >= player->getScreenH() - player->getH()
                            )
                        ) {
                            player->enemyDestroyPlayer();
                        }
                    }
                }
            }
            if (player->getState() == destroyed) break;
        }
}