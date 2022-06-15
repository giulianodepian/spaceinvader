#include "player.h"

Player::Player(int screenW, int screenH){
    Player::screenW = screenW;
    Player::screenH = screenH;
    h = 20;
    w = 40;
    x = screenW / 2 - w / 2;
    bulletH = 10;
    bulletW = 5;
    bulletX = x + w / 2;
    bulletY = screenH - h - bulletH;
    bulletDy = 5;
    dx = 5;
    state = normal;
}

void Player::movement(int direction) {
    x += dx * direction;
    if (x < 0) {
        x = 0;
    } else if (x > screenW - w) {
        x = screenW - w;
    }
    if (state == normal) {
        bulletX = x + w / 2;
    }
}

void Player::bulletMovement(){
    bulletY -= bulletDy;
    if (bulletY + bulletH < 0) {
        resetBullet();
        state = normal;
    }
}

void Player::resetBullet(){
    bulletY = screenH - h - bulletH;
    bulletX = x + w / 2 - 2;
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

entityState Player::getState() {
    return state;
}

void Player::setState(entityState state) {
    Player::state = state;
}

int Player::getBulletX() {
    return bulletX;
}

int Player::getBulletY() {
    return bulletY;
}

int Player::getBulletH() {
    return bulletH;
}

int Player::getBulletW() {
    return bulletW;
}