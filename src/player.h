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
        entityState getState();
        void setState(entityState state);
        void resetBullet();
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
};

#endif