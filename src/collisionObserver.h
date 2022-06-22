#ifndef _H_COLLISION
#define _H_COLLISION

#include "player.h"
#include "enemy.h"
#include <array>
#include <SDL2/SDL.h>

class CollisionObserver {
    public:
        void update(Player *player, std::array<std::array<Enemy *, 5>, 11> enemies);
};
#endif