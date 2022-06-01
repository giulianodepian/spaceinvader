#include "player.h"

Player::Player(int screenW, int screenH){
    Player::screenW = screenW;
    Player::screenH = screenH;
    h = 20;
    w = 40;
    x = screenW / 2 - w / 2;
    dx = 5;
}

void Player::movement(int direction) {
    x += dx * direction;
    if (x < 0) {
        x = 0;
    } else if (x > screenW - w) {
        x = screenW - w;
    }
}

int Player::getX() {
    return x;
}

int Player::getH() {
    return h;
}

int Player::getW() {
    return w;
}