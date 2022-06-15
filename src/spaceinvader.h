#ifndef _H_SPACEINVADER
#define _H_SPACEINVADER
#include <iostream>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"
#include "enemy.h"
#include "global.h"

class Player;
class Enemy;

class SpaceInvader {
    public:
        static const int SCREEN_WIDTH = 800;
        static const int SCREEN_HEIGHT = 600;
        SpaceInvader();
        ~SpaceInvader();
        void execute();
        void input();
        void update();
        void render();
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        SDL_TimerID timer;
        SDL_Surface *playerSurface;
        SDL_Texture *playerTexture;
        SDL_Surface *bulletSurface;
        SDL_Texture *bulletTexture;
        SDL_Surface *enemySmall1Surface;
        SDL_Texture *enemySmall1Texture;
        SDL_Surface *enemyMedium1Surface;
        SDL_Texture *enemyMedium1Texture;
        SDL_Surface *enemyLarge1Surface;
        SDL_Texture *enemyLarge1Texture;
        SDL_Surface *enemySmall2Surface;
        SDL_Texture *enemySmall2Texture;
        SDL_Surface *enemyMedium2Surface;
        SDL_Texture *enemyMedium2Texture;
        SDL_Surface *enemyLarge2Surface;
        SDL_Texture *enemyLarge2Texture;
        SDL_Surface *deathEnemySurface;
        SDL_Texture *deathEnemyTexture;
        Player *player;
        std::array<std::array<Enemy*, 5>, 11> enemies;
        int score;
        bool leftKeyPressed;
        bool rightKeyPressed;
        bool zWasPressed;
        bool exitProgram;
        bool detectecCollision;
};

#endif