#include "enemy.h"

Enemy::Enemy(int initialX, int initialY, enemyType type, int screenW, int screenH) {
    direction = 1;
    Enemy::screenH = screenH;
    Enemy::screenW = screenW;
    Enemy::type = type;
    switch (type) {
        case small:
            w = 8;
            break;
        case medium:
            w = 11;
            break;
        case large:
            w = 12;
            break;
        default:
            w = 12;
            break;
    };
    paddingX = 55;
    paddingY = 10;
    x = initialX * (12 + 55);
    y = initialY * (HEIGHT + 10);
    currentAnim = 1;
    state = normal;
    bulletX = initialX + w / 2;
    bulletY = initialY + HEIGHT;
    collided = false;
}

int Enemy::getX() {
    return x;
}

int Enemy::getY() {
    return y;
}

int Enemy::getW() {
    return w;
}

int Enemy::getBulletX() {
    return bulletX;
}

int Enemy::getBulletY() {
    return bulletY;
}

int Enemy::getCurrentAnim() {
    return currentAnim;
}

entityState Enemy::getState() {
    return state;
}

enemyType Enemy::getType() {
    return type;
}

void Enemy::horizontalMovement() {
    x += DX * direction;
    if (currentAnim == 1) currentAnim = 2;
    else currentAnim = 1;
}

void Enemy::verticalMovement() {
    y += DY;
    if (direction == 1) direction = -1;
    else direction = 1;
}

bool Enemy::detectCollision() {
    if (x + DX * direction > screenW - 12 || x + DX * direction < 0 + 12) return true;
    return false;
}
