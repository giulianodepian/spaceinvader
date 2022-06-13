#ifndef _H_ENEMY
#define _H_ENEMY
#include "global.h"

enum enemyType {
    small,
    medium,
    large
};

class Enemy {
    public:
        static const int BULLETH = 10;
        static const int BULLETW = 5;
        static const int HEIGHT = 23;
        static const int DX = 20;
        static const int DY = 20;
        Enemy(int initialX, int initialY, enemyType type, int screenW, int screenH);
        void horizontalMovement();
        void verticalMovement();
        bool detectCollision();
        int getY();
        int getX();
        int getBulletX();
        int getBulletY();
        int getW();
        int getCurrentAnim();
        entityState getState();
        void setState(entityState state);
        enemyType getType();
    private:
        enemyType type;
        entityState state;
        int x;
        int y;
        int w;
        int paddingX;
        int paddingY;
        int currentAnim;
        int bulletY;
        int bulletX;
        int direction;
        int screenW;
        int screenH;
        int score;
        bool collided;
};

#endif