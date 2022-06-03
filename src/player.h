#ifndef _H_PLAYER
#define _H_PLAYER

enum stateType {
    normal,
    shooting,
    detroyed
};

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
        stateType getState();
        void setState(stateType state);
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
        stateType state;
        int screenW;
        int screenH;
};

#endif