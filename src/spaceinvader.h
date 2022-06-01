#ifndef _H_SPACEINVADER
#define _H_SPACEINVADER
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"

class Player;

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
        SDL_Surface *playerSurface;
        SDL_Texture *playerTexture;
        Player *player;
        bool leftKeyPressed;
        bool rightKeyPressed;
        bool exitProgram;
};

#endif