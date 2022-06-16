#ifndef _H_SPACEINVADER
#define _H_SPACEINVADER
#include <iostream>
#include <array>
#include <string> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "player.h"
#include "enemy.h"
#include "global.h"

class Player;
class Enemy;

enum gameState {
    playing,
    ending,
    gameover,
};

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
        gameState state;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        TTF_Font *font;
        SDL_Rect scorePos;
        SDL_Rect livesPos;
        SDL_TimerID timer;
        SDL_Surface *playerSurface;
        SDL_Texture *playerTexture;
        SDL_Surface *playerDeathSurface;
        SDL_Texture *PlayerDeathTexture;
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
        SDL_Surface *gameOverTextSurface;
        SDL_Texture *gameOverTextTexture;
        Player *player;
        std::array<std::array<Enemy*, 5>, 11> enemies;
        int score;
        int lives;
        bool leftKeyPressed;
        bool rightKeyPressed;
        bool zWasPressed;
        bool exitProgram;
        bool detectecCollision;
};

#endif