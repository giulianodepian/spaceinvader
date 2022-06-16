#include "enemy.h"

Enemy::Enemy(int initialX, int initialY, enemyType type, int screenW, int screenH) {
    direction = 1;
    Enemy::screenH = screenH;
    Enemy::screenW = screenW;
    Enemy::type = type;
    switch (type) {
        case small:
            w = 23;
            score = 30;
            break;
        case medium:
            w = 26;
            score = 20;
            break;
        case large:
            w = 27;
            score = 10;
            break;
        default:
            w = 27;
            score = 10;
            break;
    };
    paddingX = 30;
    paddingY = 5;
    initialPaddingY = 50;
    x = initialX * (27 + paddingX);
    y = initialY * (HEIGHT + paddingY) + initialPaddingY;
    originalX = x;
    originalY = y;
    currentAnim = 1;
    state = normal;
    bulletX = x + w / 2;
    bulletY = y + HEIGHT;
    bulletDY = 2;
    bulletH = 10;
    bulletW = 5;
    collided = false;
    playDeathAnimation = true;
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

int Enemy::getBulletH() {
    return bulletH;
}

int Enemy::getBulletW() {
    return bulletW;
}

int Enemy::getCurrentAnim() {
    return currentAnim;
}

int Enemy::getScore() {
    return score;
}

entityState Enemy::getState() {
    return state;
}

enemyType Enemy::getType() {
    return type;
}

void Enemy::setState(entityState state) {
    Enemy::state = state;
}

bool Enemy::getPlayDeathAnimation() {
    return playDeathAnimation;
}

void Enemy::setPlayDeathAnimation(bool playDeathAnimation) {
    Enemy::playDeathAnimation = playDeathAnimation;
}

void Enemy::horizontalMovement() {
    x += DX * direction;
    if (state != shooting) bulletX = x + w / 2;
    if (currentAnim == 1) currentAnim = 2;
    else currentAnim = 1;
}

void Enemy::verticalMovement() {
    y += DY;
    if (state != shooting) bulletY = y + HEIGHT;
    if (direction == 1) direction = -1;
    else direction = 1;
    if (currentAnim == 1) currentAnim = 2;
    else currentAnim = 1;
}

void Enemy::bulletMovement() {
    bulletY += bulletDY;
    if (bulletY > screenH) {
        resetBullet();
        state = normal;
    }
}

void Enemy::resetBullet() {
    bulletY = y + HEIGHT;
    bulletX = x + w / 2;
}

bool Enemy::detectCollision() {
    if (x + DX * direction > screenW - 17 || x + DX * direction < 0 + 17) return true;
    return false;
}

void Enemy::resetPosition() {
    direction = 1;
    x = originalX;
    y = originalY;
    resetBullet();
}
