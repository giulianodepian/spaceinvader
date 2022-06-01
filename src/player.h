#ifndef _H_PLAYER
#define _H_PLAYER

class Player {
    public:
        Player(int screenW, int screenH);
        void movement(int direction);
        int getX();
        int getH();
        int getW();
    private:
        int x;
        int dx;
        int h;
        int w;
        int screenW;
        int screenH;
};

#endif