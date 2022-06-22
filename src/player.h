#ifndef _H_PLAYER
#define _H_PLAYER
#include "global.h"

class Player {
    public:
        Player(int screenW, int screenH);
        void movement(int direction);
        void bulletMovement();
        int getX();
        int getH();
        int getW();
        int getBulletX();
        int getBulletY();
        int getBulletH();
        int getBulletW();
        int getScreenH();
        int getLives();
        int getScore();
        int getKillCount();
        void setLives(int lives);
        void setScore(int score);
        void setKillCount(int killCount);
        entityState getState();
        void setState(entityState state);
        void resetBullet();
        void playerDestroyEnemy(int score);
        void enemyDestroyPlayer();
    private:
        int x;
        int dx;
        int h;
        int w;
        int bulletX;
        int bulletY;
        int bulletH;
        int bulletW;
        int bulletDy;
        entityState state;
        int screenW;
        int screenH;
        int lives;
        int score;
        int killCount;
};

#endif